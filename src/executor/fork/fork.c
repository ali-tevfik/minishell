/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 18:54:29 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/create_parse_list.h"
#include "../../../incl/minishell.h"
#include "../../../incl/built_in.h"
#include "../../executor/find_command.h"
#include "../../../incl/fork.h"
#include "../../parser/parser_data_structs.h"
#include "../../../incl/protect.h"

#include <signal.h>

extern int	g_interactive;

void	execve_func(t_pipeline *pip_line, t_list *env)
{
	char	**envp;

	envp = create_envp(env);
	find_command(pip_line->command, env);
	execve(pip_line->command[0], pip_line->command, envp);
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

void	kies_builtin_of_execve(t_pipeline *pip_line, t_list *env)
{
	if (pip_line->redirection)
		handle_redirections(pip_line);
	if (is_builtin(pip_line))
		execute_builtin(pip_line, &env);
	else
		execve_func(pip_line, env);
}

void	fork_func(t_list *pipe_lst, t_list *env, int *last_id)
{
	int			fd[2];
	int			end_file;
	int			i;
	t_pipeline	*pip_line;

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
			one_argument(pip_line, env, last_id);
		else if (i == 0)
			first_child(pip_line, env, fd);
		else if (!pipe_lst->next)
			last_child(pip_line, env, fd, last_id);
		else
			middle_child(pip_line, env, fd, end_file);
		if (end_file != -1)
		{
			protect_close(end_file);
			if (pipe_lst->next)
				end_file = fd[0];
		}
		else
			end_file = fd[0];
		pipe_lst = pipe_lst->next;
		if (pipe_lst)
			protect_close(fd[1]);
		i++;
	}
}
