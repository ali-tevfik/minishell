/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:50:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 18:06:10 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

static bool	is_char_a_delimiter(char c)
{
	int			i;
	const char	*delimiters = "|<>\'\"\n \t\0";

	i = 0;
	while (i < 9)
	{
		if (delimiters[i] == c)
			return (true);
		i++;
	}
	return (false);
}

t_token	*create_token(char *content, size_t len_content, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->content = content;
	token->len_content = len_content;
	token->type = type;
	return (token);
}

t_token	*take_word(t_char_iter *itr)
{
	int		len;
	char	*start_token;
	t_token	*token;

	len = 0;
	start_token = *itr;
	token = NULL;
	while (has_next(*itr))
	{
		if (is_char_a_delimiter(peek(*itr)) == true)
			break ;
		len++;
		next(itr);
	}
	token = create_token(start_token, len, WORD);
	return (token);
}

t_token	*take_pipe(t_char_iter *itr)
{
	t_token	*token;

	token = create_token(*itr, 1, PIPE);
	next(itr);
	return (token);
}

t_token	*take_redir_right(t_char_iter *itr)
{
	int		len;
	size_t	type;
	char	*start_token;
	t_token	*token;

	len = 1;
	type = REDIR_RIGHT_ONCE;
	start_token = *itr;
	next(itr);
	if (peek(*itr) == '>')
	{
		len++;
		type = REDIR_RIGHT_TWICE;
		next(itr);
	}
	if (peek(*itr) == '>')
		type = ERROR;
	token = create_token(start_token, len, type);
	return (token);
}
