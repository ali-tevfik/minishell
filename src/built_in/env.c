/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 15:17:13 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include <stdio.h>

/* NOTES
** Calloc needs to change to 1 instead of 2. we need only one struct.
** Protect all mallocs and free data of split.
**
*/
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
