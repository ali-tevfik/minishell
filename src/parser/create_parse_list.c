/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_parse_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:00:14 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 15:43:02 by hyilmaz       ########   odam.nl         */
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
	size_t			len_list;
	t_list			*parse_list;
	t_list			*new_list_element;
	t_pipeline		*pipeline;
	t_list_location	location;

	len_list = ft_lstsize(token_list);
	parse_list = NULL;
	location.head = token_list;
	location.list_idx = 0;
	while (1)
	{
		pipeline = create_simple_pipeline_up_until_pipe_token(location.head, \
															&location.list_idx);
		new_list_element = lstnew_protect(pipeline);
		ft_lstadd_back(&parse_list, new_list_element);
		if (location.list_idx >= len_list)
			break ;
		location.head = forward_to_list_index(token_list, location.list_idx);
	}
	return (parse_list);
}
