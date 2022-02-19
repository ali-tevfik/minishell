/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/19 01:36:14 by tevfik        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/built_in.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"

void	first_child(t_pipeline *pip_line, t_list *env, char **envp, int fd[2])
{
	int	id;

	id = fork();
	if (id == 0)
	{
		find_command(pip_line->command, env);
		if (pip_line-> redirection)
			fork_file(pip_line);
		close(fd[0]);
		dup2 (fd[1], 1);
		close(fd[1]);
		execve(pip_line->command[0], pip_line->command, envp);
		perror("Error with execve");
		exit(1);
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
		dup2 (endfile, 0);
		close(fd[0]);
		close(fd[1]);
		close(endfile);
		find_command(pip_line->command, env);
		execve(pip_line->command[0], pip_line->command, envp);
		perror("Error with execve");
		exit(1);
	}
}

void	last_child(t_pipeline *pip_line, t_list *env,
		char **envp, int fd[2], int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		find_command(pip_line->command, env);
		if (pip_line-> redirection)
			fd[1] = fork_file(pip_line);
		close(fd[1]);
		dup2 (fd[0], 0);
		close(fd[0]);
		execve(pip_line->command[0], pip_line->command, envp);
		perror("Error with execve");
		exit(1);
	}
}

void	one_argument(t_pipeline *pip_line, t_list *env,
		char *envp[], int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		find_command(pip_line->command, env);
		if (pip_line-> redirection)
			fork_file(pip_line);
		execve(pip_line->command[0], pip_line->command, envp);
		perror("Error with execve");
		exit(1);
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
		check_dolar(pipe_lst, env);
		pip_line = pipe_lst->content;
		if (pipe_lst->next)
		{
			if (pipe(fd) == -1)
				exit(0);
		}
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
