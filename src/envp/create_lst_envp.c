/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_lst_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:24:40 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/21 14:48:48 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"

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
		env = ft_calloc(2, sizeof(*env));
		if (!env)
			exit(-1);
		argument = ft_split(ft_strdup(envp[i]), '=');
		if (!argument)
			exit(0);
		env->key = argument[0];
		env->value = argument[1];
		ft_lstadd_back(&envp_, ft_lstnew(env));
		i++;
	}
	return (envp_);
}
