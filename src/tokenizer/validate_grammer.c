/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_grammer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:17:55 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/22 22:00:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate_grammer.h"

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
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (false);
		}
		else if ((((t_token *)(head->content))->type == REDIRECTION || \
				((t_token *)(head->content))->type == PIPE) && \
				previous_type == REDIRECTION)
		{
			printf("minishell: syntax error near unexpected token <, > or |\n");
			return (false);
		}
		previous_type = ((t_token *)(head->content))->type;
		head = head->next;
	}
	return (true);
}
