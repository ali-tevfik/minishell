/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:35:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 13:00:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_quotes.h"

static t_token	*handle_empty_quotes(t_char_iter *itr, char c)
{
	t_token	*token;
	char	*content;

	next(itr);
	content = ft_strdup("");
	if (content == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	if (c == '\'')
		token = create_token(content, QUOTE);
	else
		token = create_token(content, DQUOTE);
	return (token);
}

static t_token	*handle_filled_quotes(t_char_iter *itr, char *start_string,
										size_t len, char c)
{
	t_token	*token;
	char	*content;

	next(itr);
	content = ft_substr(start_string, 1, len - 1);
	if (content == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	if (c == '\'')
		token = create_token(content, QUOTE);
	else
		token = create_token(content, DQUOTE);
	return (token);
}

t_token	*take_quotes(t_char_iter *itr, char c)
{
	size_t	len;
	char	*start_input;
	char	*content;
	t_token	*token;

	len = 1;
	start_input = *itr;
	next(itr);
	if (peek(*itr) == c)
		return (handle_empty_quotes(itr, c));
	while (has_next(*itr))
	{
		if (peek(*itr) == c)
			return (handle_filled_quotes(itr, start_input, len, c));
		len++;
		next(itr);
	}
	content = ft_substr(start_input, 1, len);
	if (content == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	token = create_token(content, ERROR);
	return (token);
}
