/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_grammer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:17:55 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 14:22:52 by hyilmaz       ########   odam.nl         */
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

bool	is_redirection_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == READ || type == WRITE || \
		type == HERE_DOC || type == APPEND)
		return (true);
	return (false);
}

static bool	is_token_of_type(t_token *token, t_token_type type)
{
	if (token->type == type)
		return (true);
	return (false);
}

static bool	init_validation(t_list *token_list, t_list **head,
							t_list **previous_token)
{
	*previous_token = token_list;
	*head = token_list->next;
	if (((t_token *)((*previous_token)->content))->type == ERROR || \
		((t_token *)((*previous_token)->content))->type == AMPERSAND || \
		((t_token *)((*previous_token)->content))->type == SEMICOLON)
		return (print_unexpected_token_message((*previous_token)->content));
	return (true);
}

bool	validate_grammer(t_list *token_list)
{
	t_list	*head;
	t_list	*previous_token;

	if (!init_validation(token_list, &head, &previous_token))
		return (false);
	while (head)
	{
		if (is_token_of_type(head->content, PIPE) && \
			is_token_of_type(previous_token->content, PIPE))
			return (print_unexpected_token_message((t_token *)(head->content)));
		else if ((is_redirection_token(head->content) || \
				is_token_of_type(head->content, PIPE)) && \
				is_redirection_token(previous_token->content))
			return (print_unexpected_token_message(head->content));
		else if (((t_token *)(head->content))->type == ERROR || \
				((t_token *)(head->content))->type == AMPERSAND || \
				((t_token *)(head->content))->type == SEMICOLON)
			return (print_unexpected_token_message(head->content));
		previous_token = head;
		head = head->next;
	}
	if (is_token_of_type(previous_token->content, PIPE) || \
		is_redirection_token(previous_token->content))
		return (print_unexpected_token_message(previous_token->content));
	return (true);
}
