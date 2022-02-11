/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_envp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:25:44 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/11 19:25:54 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

t_list	*delete_env(t_list *old_lst, t_list **envp)
{
	t_list	*fake;

	if (!old_lst)
	{
		old_lst = *envp;
		*envp = (*envp)->next;
		free(old_lst->content);
		free(old_lst);
		return (*envp);
	}
	fake = old_lst->next;
	old_lst->next = old_lst->next->next;
	free(fake->content);
	free(fake);
	return (old_lst);
}
