/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/28 15:30:13 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	remove_var(t_list **lst, char *key)
{
	t_list	**tail;
	t_list	*rest;
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->next->content, key, ft_strlen(key))
			== 0 && ft_strlen(key) == ft_strlen(tmp->next->content))
			break ;
		tmp = tmp->next;
	}
	tail = &tmp;
	rest = tmp->next->next;
	free((*tail)->next->content);
	free((*tail)->next);
	(*tail)->next = rest;
}

void	unset_command(t_list *envp, char *argument)
{
	match_key_env(envp, argument + 6, 1);
}
