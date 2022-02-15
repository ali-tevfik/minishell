/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:15:03 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 17:29:16 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"

char	*expander(char *txt, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (match_str(env->key, txt) == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
