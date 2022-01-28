/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 17:19:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/28 15:19:33 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

// void	free_func(void *data)
// {
// 	free(data);
// }



void	remove_var(t_list **lst, char *key)
{
	t_list	**tail;
	t_list	*rest;
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->next->content, key, ft_strlen(key))
			== 0 && ft_strlen(key) == ft_strlen(tmp->next->content))
			break ;
		tmp = tmp->next;
	}
	tail = &tmp;
	rest = tmp->next->next;
	free((*tail)->next->content);
	free((*tail)->next);
	(*tail)->next = rest;
}



void	unset_command(t_list *envp, char *argument)
{
	// t_list	*fake;
	char	*text;
	// char	**envp_;

	text = ft_split(skip_space(argument + 6), '=')[0];
	// while (envp != NULL)
	// {
	// 	if (envp->next)
	// 	{
	// 		envp_ = ft_split(envp->next->content, '=');
	// 		if (ft_strncmp(envp_[0], text, ft_strlen(envp_[0])) == 0)
	// 		{
	// 			fake = envp->next->next;
	// 			ft_lstdelone(envp->next, free_func);
	// 			envp->next = fake;
	// 			break ;
	// 		}
	// 	}
	// 	envp = envp->next;
	// }
	match_key_env(envp, argument + 6, 1);


}
