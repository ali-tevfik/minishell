/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:15:03 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/02 13:15:54 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/commands.h"

char	*expander(char *txt, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (ft_strncmp(env->key, txt, ft_strlen(env->key)) == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
