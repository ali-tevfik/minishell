/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_envp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 20:16:20 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 17:29:42 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/built_in.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"

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
		exit(1);
	i = 0;
	while (env_lst)
	{
		env = env_lst->content;
		small_envp = ft_strjoin(env->key, "=");
		if (!small_envp)
			exit(1);
		envp[i] = ft_strjoin(small_envp, env->value);
		if (!envp[i])
			exit(1);
		i++;
		env_lst = env_lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
