/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/02 17:00:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/create_parse_list.h"
#include "../../../incl/minishell.h"
#include "../../../incl/built_in.h"
#include "../../executor/find_command.h"
#include "../../../incl/fork.h"
#include "../../parser/parser_data_structs.h"

extern int g_interactive;

void execve_func(t_pipeline *pip_line, char **envp, t_list *env)
{
	find_command(pip_line->command, env);
	execve(pip_line->command[0], pip_line->command, envp);
	perror("Error with execve");
	exit(1);
}

void	first_child(t_pipeline *pip_line, t_list *env, char **envp, int fd[2])
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (pip_line->redirection)
			fork_file(pip_line);	/* no assigning return value , can we write to file from here */
		close(fd[0]);		/* no protection for close */
		dup2 (fd[1], 1);	/* no protections for dup */
		close(fd[1]);		/* pipe dup after redirection to file?, first always do pipe dups, than if files present, dup files */
		if (check_built_in_file(pip_line))	/* change function name to is_builtin, easier to read */
			built_in(pip_line, &env);		/* change name to execute_builtin */
		else
			execve_func(pip_line, envp, env);	/* change name to execute_binary */
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
		dup2 (fd[1], 1);
		dup2 (endfile, 0);		/* no redirection for files here? */
		close(fd[0]);
		close(fd[1]);
		close(endfile);
		if (check_built_in_file(pip_line))
			built_in(pip_line, &env);
		else
			execve_func(pip_line, envp, env);
		exit(0);
	}
}

void	last_child(t_pipeline *pip_line, t_list *env,
		char **envp, int fd[2], int *lastid)
{
	*lastid = fork();

	if (*lastid == 0)
	{
		if (pip_line->redirection)
			fd[1] = fork_file(pip_line);
		close(fd[1]);						/* closing what is just created? */
		dup2 (fd[0], 0);
		close(fd[0]);
		if (check_built_in_file(pip_line))
			built_in(pip_line, &env);
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
			fork_file(pip_line);
		if (check_built_in_file(pip_line))
			built_in(pip_line, &env);
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

	envp = create_2d_env_array_from_list(env);
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
		end_file = fd[0];
		pipe_lst = pipe_lst->next;
		if (pipe_lst)
			close(fd[1]);
		i++;
	}
}
