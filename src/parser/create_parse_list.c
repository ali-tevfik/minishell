/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_parse_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:00:14 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/27 12:36:57 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "create_parse_list.h"

static t_list	*forward_to_list_index(t_list *token_list, size_t list_idx)
{
	size_t	i;

	i = 0;
	while (token_list != NULL && i < list_idx)
	{
		token_list = token_list->next;
		i++;
	}
	return (token_list);
}

t_list	*create_parse_list(t_list *token_list)
{
	size_t		len_list;
	size_t		list_idx;
	t_list		*parse_list;
	t_list		*head;
	t_command	*command;

	len_list = ft_lstsize(token_list);
	parse_list = NULL;
	head = token_list;
	list_idx = 0;
	while (1)
	{
		command = create_simple_command_up_until_pipe_token(head, &list_idx);
		ft_lstadd_back(&parse_list, ft_lstnew(command));
		if (list_idx >= len_list)
			break ;
		head = forward_to_list_index(token_list, list_idx);
	}
	return (parse_list);
}
