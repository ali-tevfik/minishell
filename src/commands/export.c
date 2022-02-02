/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/02 13:12:19 by adoner        ########   odam.nl         */
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
	t_list	*old_lst;
	t_list	*head;
	t_env	*env;

	old_lst = NULL;
	head = *envp;
	while (head != NULL)
	{
		env = head->content;
		if (ft_strncmp(env->key, argument, ft_strlen(env->key)) == 0)
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
	char	**argument;
	t_env	*env;

	if (ft_strrchr(line, '=') == 0)
		return ;
	argument = ft_split(skip_space(line + 6), '=');
	if (!argument)
		exit(0);
	if (!ft_isalpha(argument[0][0]) && argument[0][0] != 95)
		return ;
	if (match_key_env(envp, argument[0], 0) == 0)
	{
		env = ft_calloc(2, sizeof(env));
		env->key = argument[0];
		if (argument[1])
			env->value = argument[1];
		else
			env->value = "";
		ft_lstadd_back(envp, ft_lstnew(env));
	}
}
