/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_word.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:35:56 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/21 17:54:25 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_word.h"

/*
** Handles quotes inside a WORD. If no closing quote, error is set to 1.
** It consumer the iterator up until the next character after the
** closing (double) quote.
*/
static void	handle_quotes(t_char_iter *itr, int *len, int *error)
{
	char	quote_type;

	*len += 1;
	quote_type = peek(*itr);
	next(itr);
	*error = 0;
	while (has_next(*itr))
	{
		*len += 1;
		if (peek(*itr) == quote_type)
		{
			next(itr);
			return ;
		}
		next(itr);
	}
	*error = 1;
}

/*
** Helper function that creates the content and token.
*/

static t_token	*create_content_and_get_token(char *start_token, int len,
											int error)
{
	char	*content;
	t_token	*token;

	content = ft_substr(start_token, 0, len);
	if (content == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	if (error == 0)
		token = create_token(content, WORD);
	else
		token = create_token(content, ERROR);
	return (token);
}

/*
** Takes the WORD token. Includes quotes. If quotes are not closed,
** ERROR token is returned.
*/

t_token	*take_word(t_char_iter *itr)
{
	int		len;
	int		error;
	char	*start_token;
	t_token	*token;

	len = 0;
	error = 0;
	start_token = *itr;
	token = NULL;
	while (has_next(*itr))
	{
		if (is_char_a_delimiter(peek(*itr)) == true)
			break ;
		if (peek(*itr) == '\'' || peek(*itr) == '\"')
		{
			handle_quotes(itr, &len, &error);
			if (error == 1)
				break ;
			continue ;
		}
		len++;
		next(itr);
	}
	return (create_content_and_get_token(start_token, len, error));
}
