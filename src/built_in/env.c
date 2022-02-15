/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 14:37:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include <stdio.h>

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
