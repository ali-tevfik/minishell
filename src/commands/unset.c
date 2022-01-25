/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/25 18:37:10 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	free_func(void *data)
{
	free(data);
}

void	unset_command(t_list *envp, char *argument)
{
	t_list	*fake;
	char	*text;
	char	**envp_;

	text = ft_split(skip_space(argument + 6), '=')[0];
	while (envp != NULL)
	{
		if (envp->next)
		{
			envp_ = ft_split(envp->next->content, '=');
			if (ft_strncmp(envp_[0], text, ft_strlen(envp_[0])) == 0)
			{
				fake = envp->next->next;
				ft_lstdelone(envp->next, free_func);
				envp->next = fake;
				break ;
			}
		}
		envp = envp->next;
	}
}
