/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_2d_env_array_from_list.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 20:16:20 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/01 13:19:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/built_in.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"
#include "../../incl/protect.h"

char	**create_2d_env_array_from_list(t_list *env_list)
{
	int		i;
	int		lst_size;
	char	**envp;
	char	*key_plus_equal_sign;
	t_env	*env;

	lst_size = ft_lstsize(env_list);
	envp = ft_calloc(lst_size + 1, sizeof(*envp));
	if (!envp)
		exit(-1);
	i = 0;
	while (env_list)
	{
		env = env_list->content;
		key_plus_equal_sign = join_protect(env->key, "=");
		envp[i] = join_protect(key_plus_equal_sign, env->value);
		//free(key_plus_equal_sign);
		env_list = env_list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
