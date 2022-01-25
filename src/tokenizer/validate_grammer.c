/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_grammer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:17:55 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/23 21:46:10 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate_grammer.h"

static bool	print_unexpected_token_message(t_token *token)
{
	printf("minishell: syntax error near unexpected token '%.*s'\n", \
		(int)token->len_content, token->content);
	return (false);
}

bool	validate_grammer(t_list *token_list)
{
	t_list	*head;
	int		previous_type;

	head = token_list;
	previous_type = ((t_token *)(head->content))->type;
	head = head->next;
	while (head)
	{
		if (((t_token *)(head->content))->type == PIPE && previous_type == PIPE)
			return (print_unexpected_token_message((t_token *)(head->content)));
		else if ((((t_token *)(head->content))->type == REDIRECTION || \
				((t_token *)(head->content))->type == PIPE) && \
				previous_type == REDIRECTION)
			return (print_unexpected_token_message((t_token *)(head->content)));
		else if (((t_token *)(head->content))->type == ERROR)
			return (print_unexpected_token_message((t_token *)(head->content)));
		previous_type = ((t_token *)(head->content))->type;
		head = head->next;
	}
	return (true);
}
