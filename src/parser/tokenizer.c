/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/17 18:05:06 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->content = content;
	token->type = type;
	return (token);
}

t_list	*tokenize_input(char *input_string)
{
	t_list	*token_list;
	t_token	*token;

	token = create_token(input_string, WORD);
	token_list = ft_lstnew(token);
	return (token_list);
}
