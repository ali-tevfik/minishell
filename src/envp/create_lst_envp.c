/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lst_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:24:40 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/03 13:34:08 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../../incl/protect.h"

t_list	*create_env_list(char *envp[])
{
	int		i;
	t_list	*env_list;
	t_env	*env;
	char	**argument;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		env = calloc_protect(1, sizeof(*env));
		argument = split_protect(strdup_protect(envp[i]), '=');
		env->key = argument[0];
		env->value = argument[1];
		ft_lstadd_back(&env_list, ft_lstnew(env));
		i++;
	}
	return (env_list);
}
