/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_grammer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:17:55 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 13:11:12 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate_grammer.h"

static bool	print_unexpected_token_message(t_token *token)
{
	char	content[3];

	if (token->content == NULL)
	{
		if (token->type == PIPE)
			ft_strlcpy(content, "|", 2);
		else if (token->type == READ)
			ft_strlcpy(content, "<", 2);
		else if (token->type == HERE_DOC)
			ft_strlcpy(content, "<<", 3);
		else if (token->type == WRITE)
			ft_strlcpy(content, ">", 2);
		else if (token->type == APPEND)
			ft_strlcpy(content, ">>", 3);
		else if (token->type == AMPERSAND)
			ft_strlcpy(content, "&", 2);
		else if (token->type == SEMICOLON)
			ft_strlcpy(content, ";", 2);
		printf("minishell: syntax error near unexpected token '%s'\n", content);
	}
	else
		printf("minishell: syntax error near unexpected token '%s'\n", \
				token->content);
	return (false);
}

static bool	is_redirection(t_token_type type)
{
	if (type == READ || type == WRITE || \
		type == HERE_DOC || type == APPEND)
		return (true);
	return (false);
}

bool	validate_grammer(t_list *token_list)
{
	t_list	*head;
	int		previous_type;

	head = token_list;
	previous_type = ((t_token *)(head->content))->type;
	if (ft_lstsize(head) == 1 && (((t_token *)(head->content))->type == PIPE || \
		is_redirection(((t_token *)(head->content))->type)))
		return (print_unexpected_token_message((t_token *)(head->content)));
	head = head->next;
	while (head)
	{
		if (((t_token *)(head->content))->type == PIPE && previous_type == PIPE)
			return (print_unexpected_token_message((t_token *)(head->content)));
		else if ((is_redirection(((t_token *)(head->content))->type) || \
				((t_token *)(head->content))->type == PIPE) && \
				is_redirection(previous_type))
			return (print_unexpected_token_message((t_token *)(head->content)));
		else if (((t_token *)(head->content))->type == ERROR || \
				((t_token *)(head->content))->type == AMPERSAND || \
				((t_token *)(head->content))->type == SEMICOLON)
			return (print_unexpected_token_message((t_token *)(head->content)));
		previous_type = ((t_token *)(head->content))->type;
		head = head->next;
	}
	return (true);
}
