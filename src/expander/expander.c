/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:15:03 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/17 15:37:11 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"

char	*expander(char *txt, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (strings_are_equal(env->key, txt))
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
