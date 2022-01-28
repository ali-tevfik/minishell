/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/28 20:03:35 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

t_list	*delete_env(t_list *old_lst, t_list **envp)
{
	t_list	*fake;

	if (!old_lst)
	{
		old_lst = *envp;
		*envp = (*envp)->next;
		free(old_lst->content);
		free(old_lst);
		return (*envp);
	}
	fake = old_lst->next;
	old_lst->next = old_lst->next->next;
	free(fake->content);
	free(fake);
	return (old_lst);
}

int	match_key_env(t_list **envp, char *argument, int where)
{
	char	*text;
	char	*env_;
	t_list	*old_lst;
	t_list	*head;

	old_lst = NULL;
	head = *envp;
	text = ft_split(skip_space(argument), '=')[0];
	if (!text)
		exit(0);
	while (head != NULL)
	{
		env_ = ft_split(head->content, '=')[0];
		if (!env_)
			exit(0);
		if (ft_strncmp(env_, text, ft_strlen(env_)) == 0)
		{
			if (where == 1)
				delete_env(old_lst, envp);
			return (1);
		}
		old_lst = head;
		head = head->next;
	}
	return (0);
}

void	export_command(t_list **envp, char *line)
{
	char	*argument;

	argument = ft_strdup(skip_space(line + 6));
	if (!argument)
		exit(0);
	if (ft_strrchr(argument, '=') == 0)
		return ;
	if (!ft_isalpha(argument[0]))
		return ;
	if (match_key_env(envp, argument, 0) == 0)
		ft_lstadd_back(envp, ft_lstnew(argument));
}
