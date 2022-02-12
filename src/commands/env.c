/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/12 12:53:31 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"
#include <stdio.h>

/* NOTES
** Calloc needs to change to 1 instead of 2. we need only one struct.
** Protect all mallocs and free data of split.
**
*/

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
		env = ft_calloc(1, sizeof(*env));
		argument = ft_split(ft_strdup(envp[i]), '=');
		if (!argument)
			exit(0);
		env->key = ft_strdup(argument[0]);
		env->value = ft_strdup(argument[1]);
		ft_lstadd_back(&envp_, ft_lstnew(env));
		i++;
	}
	return (envp_);
}

void	env_commands(t_list *envp)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		printf("%s=%s\n", env->key, env->value);
		envp = envp->next;
	}
}
