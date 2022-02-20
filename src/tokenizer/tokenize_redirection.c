/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_redirection.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:45:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/19 15:08:54 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_redirection.h"

t_token	*take_redirection(t_char_iter *itr)
{
	size_t	type;
	t_token	*token;

	if (**itr == '<')
		type = READ;
	else
		type = WRITE;
	next(itr);
	if (type == READ && peek(*itr) == '<')
	{
		type = HERE_DOC;
		next(itr);
	}
	else if (type == WRITE && peek(*itr) == '>')
	{
		type = APPEND;
		next(itr);
	}
	token = create_token(NULL, type);
	return (token);
}

// if ((*start_token == '>' && peek(*itr) == '>') ||
// 	(*start_token == '<' && peek(*itr) == '<'))
// {
// 	len++;
// 	type = REDIRECTION;
// 	next(itr);
// }