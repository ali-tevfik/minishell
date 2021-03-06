/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:51:41 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/built_in_utils.h"
#include "../../incl/minishell.h"

int	unset_command(t_list **envp, t_pipeline *pipe_line)
{
	int	i;
	int	exit_code;

	exit_code = 1;
	i = 1;
	while (pipe_line->command[i])
	{
		if (!ft_isname(pipe_line->command[i]))
			print_error("unset", "not a valid identifier");
		else
		{
			match_key_env(envp, pipe_line->command[i]);
			exit_code = 0;
		}
		i++;
	}
	return (exit_code);
}
