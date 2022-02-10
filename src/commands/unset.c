/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/10 18:36:45 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	unset_command(t_list **envp, t_pipeline *pipe_line)
{
	int	i;

	i = 1;
	while (pipe_line->command[i])
	{
		match_key_env(envp, pipe_line->command[i], 1);
		i++;
	}
}
