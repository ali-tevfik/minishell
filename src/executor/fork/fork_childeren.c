/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_childeren.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:01:43 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 12:48:46 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/create_parse_list.h"
#include "../../../incl/minishell.h"
#include "../../../incl/built_in.h"
#include "../../executor/find_command.h"
#include "../../../incl/fork.h"
#include "../../parser/parser_data_structs.h"
#include <signal.h>

void	first_child(t_pipeline *pip_line, t_list *env, int fd[2])
{
	int	id;

	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		kies_builtin_of_execve(pip_line, env);
		exit(0);
	}
}

void	middle_child(t_pipeline *pip_line, t_list *env, int fd[2], int endfile)
{
	int		id;

	id = fork();
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(endfile, 0);
		close(fd[0]);
		close(fd[1]);
		close(endfile);
		kies_builtin_of_execve(pip_line, env);
		exit(0);
	}
}

void	last_child(t_pipeline *pip_line, t_list *env, int fd[2], int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		kies_builtin_of_execve(pip_line, env);
		exit(0);
	}
}

void	one_argument(t_pipeline *pip_line, t_list *env, int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		kies_builtin_of_execve(pip_line, env);
		exit(0);
	}
	else
		if (strings_are_equal(pip_line->command[0], "cd")
			|| strings_are_equal(pip_line->command[0], "export")
			|| strings_are_equal(pip_line->command[0], "unset"))
			execute_builtin(pip_line, &env);
}
