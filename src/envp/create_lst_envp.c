/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lst_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:24:40 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/25 16:50:18 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../../incl/protect.h"

t_list	*add_envp(char *envp[])
{
	t_list	*envp_;
	t_env	*env;
	int		i;
	char	**argument;

	i = 0;
	envp_ = NULL;
	while (envp[i])
	{
		env = calloc_protect(2, sizeof(*env));
		if (!env)
			exit(-1);
		argument = split_protect(strdup_protect(envp[i]), '=');
		env->key = argument[0];
		env->value = argument[1];
		ft_lstadd_back(&envp_, ft_lstnew(env));
		i++;
	}
	return (envp_);
}
