/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_dquotes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:06:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/24 11:42:30 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_dquotes.h"

t_token	*take_double_quotes(t_char_iter *itr)
{
	size_t	len;
	char	*start_input;
	t_token	*token;

	len = 1;
	start_input = *itr;
	next(itr);
	while (has_next(*itr))
	{
		if (peek(*itr) == '\"')
		{
			len++;
			next(itr);
			token = create_token(start_input, len, DQUOTE);
			return (token);
		}
		len++;
		next(itr);
	}
	token = create_token(start_input, len, ERROR);
	return (token);
}