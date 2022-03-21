/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/18 17:05:51 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
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
			printf("unset: `%s': not a valid identifier\n",
				pipe_line->command[i]);
		else
		{
			match_key_env(envp, pipe_line->command[i]);
			exit_code = 0;
		}
		i++;
	}
	return (exit_code);
}
