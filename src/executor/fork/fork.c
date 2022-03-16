/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/16 16:29:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/create_parse_list.h"
#include "../../../incl/minishell.h"
#include "../../../incl/built_in.h"
#include "../../executor/find_command.h"
#include "../../../incl/fork.h"
#include "../../parser/parser_data_structs.h"

#include <signal.h>

extern int g_interactive;

void execve_func(t_pipeline *pip_line, char **envp, t_list *env)
{
	find_command(pip_line->command, env);
	execve(pip_line->command[0], pip_line->command, envp);
	// perror("Error with execve");
	// exit(1);
	if (errno == ENOENT)
	{
		printf("minishell: %s: %s\n", pip_line->command[0], strerror(errno));
		exit (127);
	}
	else if (errno == EACCES)
	{
		printf("minishell: %s: %s\n", pip_line->command[0], strerror(errno));
		exit(126);
	}
}

void	first_child(t_pipeline *pip_line, t_list *env, char **envp, int fd[2])
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (pip_line->redirection)
			handle_redirections(pip_line);
		close(fd[0]);				// close read-end of the pipe
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);				// close write-end of the pipe
		if (is_builtin(pip_line))
			execute_builtin(pip_line, &env);
		else
			execve_func(pip_line, envp, env);
		exit(0);
	}
}

void	middle_child(t_pipeline *pip_line, t_list *env,
		char **envp, int fd[2], int endfile)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		dup2 (fd[1], STDOUT_FILENO);	// Write to current pipe
		dup2 (endfile, 0);				// Read from previous pipe
		close(fd[0]);					// Close read-end current pipe
		close(fd[1]);					// Close write-end current pipe
		close(endfile);					// Close read-end previous pipe.
		if (pip_line-> redirection)
			handle_redirections(pip_line);
		if (is_builtin(pip_line))
			execute_builtin(pip_line, &env);
		else
			execve_func(pip_line, envp, env);
		exit(0);
	}
}

void	last_child(t_pipeline *pip_line, t_list *env,
		char **envp, int fd[2], int *lastid)
{
	*lastid = fork();
	// note: using previous pipe, no pipe created in current loop because last command.
	if (*lastid == 0)
	{
		if (pip_line->redirection)
			handle_redirections(pip_line);
		close(fd[1]);						// close write-end previous pipe (was already closed in middle child?)
		dup2(fd[0], STDIN_FILENO);			// read from read-end previous pipe
		close(fd[0]);						// close read-end previous pipe.

		if (is_builtin(pip_line))
			execute_builtin(pip_line, &env);
		else
			execve_func(pip_line, envp, env);
		exit(0);
	}
}

void	one_argument(t_pipeline *pip_line, t_list *env,
		char *envp[], int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		if (pip_line->redirection)
			handle_redirections(pip_line);
		if (is_builtin(pip_line))
			execute_builtin(pip_line, &env);
		else
			execve_func(pip_line, envp, env);
		exit(0);
	}

}

void	fork_func(t_list *pipe_lst, t_list *env, int *last_id)
{
	int			fd[2];
	int			end_file;
	int			i;
	t_pipeline	*pip_line;
	char		**envp;

	envp = create_envp(env);
	i = 0;
	end_file = -1;
	while (pipe_lst)
	{
		pip_line = pipe_lst->content;
		if (pipe_lst->next)
		{
			if (pipe(fd) == -1)
				exit(0);
		}
		g_interactive = 0;
		if (i == 0 && !pipe_lst->next)
			one_argument(pip_line, env, envp, last_id);
		else if (i == 0)
			first_child(pip_line, env, envp, fd);
		else if (!pipe_lst->next)
			last_child(pip_line, env, envp, fd, last_id);
		else
			middle_child(pip_line, env, envp, fd, end_file);
		if (end_file != -1)			// if there is already an end_file
		{
			close(end_file);		// close it
			if (pipe_lst->next)		// if we have a command coming up
				end_file = fd[0];	// set end_file
		}
		else						// if no end_file, set equal to read-end current pipe
			end_file = fd[0];
		pipe_lst = pipe_lst->next;
		if (pipe_lst)
			close(fd[1]);
		i++;
	}
}
