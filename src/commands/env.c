/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/25 18:36:27 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

t_list	*add_envp(char *envp[])
{
	t_list	*envp_;
	int		i;
	char	*argument;

	i = 0;
	envp_ = NULL;
	while (envp[i])
	{
		argument = ft_strdup(envp[i]);
		if (!argument)
			exit(0);
		ft_lstadd_back(&envp_, ft_lstnew(argument));
		i++;
	}
	return (envp_);
}

void	env_commands(t_list *envp)
{
	while (envp != NULL)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
}
