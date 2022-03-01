/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lst_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:24:40 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/01 13:06:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../../incl/protect.h"

// static void	free_2d_string_array(char **string_array)
// {
// 	int	i;

// 	i = 0;
// 	while (string_array[i] != NULL)
// 	{
// 		free(string_array[i]);
// 		i++;
// 	}
// 	free(string_array);
// }

t_list	*add_envp(char *envp[])
{
	int		i;
	char	**key_value_string;
	t_env	*env;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		env = calloc_protect(1, sizeof(*env));
		if (!env)
			exit(-1);
		key_value_string = split_protect(envp[i], '=');
		env->key = key_value_string[0];
		env->value = key_value_string[1];
		free(key_value_string);
		ft_lstadd_back(&env_list, ft_lstnew(env));
		i++;
	}
	return (env_list);
}
