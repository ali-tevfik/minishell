/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/28 15:08:01 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include <stdio.h>

int	env_command(t_list *envp)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		printf("%s=%s\n", env->key, env->value);
		envp = envp->next;
	}
	return (0);
}
