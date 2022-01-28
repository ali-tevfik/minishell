/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/28 18:21:39 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	unset_command(t_list **envp, char *argument)
{
	match_key_env(envp, argument + 6, 1);
	// t_list *fake;
	// fake = envp;
	// envp = envp->next;
	// free(fake->content);
	// free(fake);
}
