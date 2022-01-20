/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:50:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:06:32 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

bool	is_char_a_delimiter(char c)
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
