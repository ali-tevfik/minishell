/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:15:03 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/04 11:19:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"

char	*expander(char *txt, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		// if (match_str(env->key, txt) == 0)
		// 	return (env->value);
		if (strings_are_equal(env->key, txt))
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
