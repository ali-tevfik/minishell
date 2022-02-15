/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_envp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:27:10 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/11 19:27:10 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

int	match_key_env(t_list **envp, char *argument)
{
	t_list	*old_lst;
	t_list	*head;
	t_env	*env;

	old_lst = NULL;
	head = *envp;
	while (head != NULL)
	{
		env = head->content;
		if (match_str(env->key, argument) == 0)
		{
			delete_env(old_lst, envp);
			return (0);
		}
		old_lst = head;
		head = head->next;
	}
	return (0);
}
