/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_envp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 20:16:20 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/25 16:50:34 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/built_in.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"
#include "../../incl/protect.h"

char	**create_envp(t_list *env_lst)
{
	int		i;
	int		lst_size;
	char	**envp;
	char	*small_envp;
	t_env	*env;

	lst_size = ft_lstsize(env_lst);
	envp = (char **)malloc(sizeof(envp) * (lst_size + 1));
	if (!envp)
		exit(-1);
	i = 0;
	while (env_lst)
	{
		env = env_lst->content;
		small_envp = join_protect(env->key, "=");
		envp[i] = join_protect(small_envp, env->value);
		i++;
		env_lst = env_lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
