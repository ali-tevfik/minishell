/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/21 19:11:34 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

t_list	*add_envp(char *envp[])
{
	t_list	*envp_;
	int		i;

	i = 1;
	envp_ = NULL;
	envp_ = ft_lstnew(envp[0]);
	while (envp[i])
	{
		ft_lstadd_back(&envp_, ft_lstnew(envp[i]));
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
