/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_word.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:35:56 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/31 16:23:59 by adoner        ########   odam.nl         */
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
** Create the content which is going inside of the token.
*/

static char	*create_content(char *start_token, int len,
							t_list *env, int exitcode)
{
	char	*content;
	char	*expanded_content;

	content = substr_protect(start_token, 0, len);
	expanded_content = expand_input_string(content, env, exitcode);
	free(content);
	if (expanded_content[0] == '\0')
		return (NULL);
	return (expanded_content);
}

/*
** Create token with content inside of it.
*/

static t_token	*create_word_token(char *content, int error)
{
	t_token	*token;

	if (content == NULL)
		return (NULL);
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

t_token	*take_word(t_char_iter *itr, t_list *env, int exitcode)
{
	int		len;
	int		error;
	char	*start_token;
	char	*content;

	len = 0;
	error = 0;
	start_token = *itr;
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
	content = create_content(start_token, len, env, exitcode);
	return (create_word_token(content, error));
}
