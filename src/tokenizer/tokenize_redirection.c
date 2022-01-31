/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_redirection.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:45:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:16:15 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_redirection.h"

t_token	*take_redirection(t_char_iter *itr)
{
	int		len;
	size_t	type;
	char	*start_token;
	t_token	*token;

	len = 1;
	type = REDIRECTION;
	start_token = *itr;
	next(itr);
	if ((*start_token == '>' && peek(*itr) == '>') || \
		(*start_token == '<' && peek(*itr) == '<'))
	{
		len++;
		type = REDIRECTION;
		next(itr);
	}
	token = create_token(start_token, len, type);
	return (token);
}
