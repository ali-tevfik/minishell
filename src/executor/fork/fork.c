/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:14:15 by adoner        ########   odam.nl         */
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
	if (pip_line->command[0])
	{
		find_command(pip_line->command, env);
		execve(pip_line->command[0], pip_line->command, envp);
	}
	if (errno == ENOENT)
	{
		perror("minishell:");
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
		execute_builtin(pip_line, &env, 0);
	else
		execve_func(pip_line, env);
}

int	fork_start(int i, t_list *pipe_lst, t_list *env, t_dup2 *dup_item)
{
	t_pipeline	*pip_line;

	pip_line = pipe_lst->content;
	if (i == 0 && !pipe_lst->next)
		one_argument(pip_line, env, dup_item->last_id);
	else if (i == 0)
		first_child(pip_line, env, dup_item->fd);
	else if (!pipe_lst->next)
		last_child(pip_line, env, dup_item->fd, dup_item->last_id);
	else
		middle_child(pip_line, env, dup_item->fd, dup_item->end_file);
	i++;
	return (i);
}

void	fork_func(t_list *pipe_lst, t_list *env, int *last_id)
{
	t_dup2		dup_item;
	int			i;

	i = 0;
	dup_item.end_file = -1;
	dup_item.last_id = last_id;
	while (pipe_lst)
	{
		if (pipe_lst->next)
			if (pipe(dup_item.fd) == -1)
				exit(0);
		g_interactive = 0;
		i = fork_start(i, pipe_lst, env, &dup_item);
		if (dup_item.end_file != -1)
		{
			protect_close(dup_item.end_file);
			if (pipe_lst->next)
				dup_item.end_file = dup_item.fd[0];
		}
		else
			dup_item.end_file = dup_item.fd[0];
		pipe_lst = pipe_lst->next;
		if (pipe_lst)
			protect_close(dup_item.fd[1]);
	}
}
