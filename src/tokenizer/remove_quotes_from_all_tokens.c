/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_from_all_tokens.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 10:21:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/31 15:33:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "remove_quotes_from_all_tokens.h"

static char	*add_char_to_string(char *string, char c)
{
	size_t	len;
	char	*new_string;

	len = ft_strlen(string);
	new_string = calloc_protect(len + 2, sizeof(*new_string));
	ft_memmove(new_string, string, len);
	free(string);
	new_string[len] = c;
	new_string[len + 1] = '\0';
	return (new_string);
}

/*
** Handles nested quotes.
*/

int	forward_quote_pair(char *line)
{
	int		i;
	bool	open_quotes;
	bool	open_double_quotes;

	i = 0;
	open_quotes = false;
	open_double_quotes = false;
	while (line[i])
	{
		if (line[i] == '\"' && !open_quotes)
		{
			open_double_quotes = !open_double_quotes;
			if (!open_double_quotes)
				return (i);
		}
		if (line[i] == '\'' && !open_double_quotes)
		{
			open_quotes = !open_quotes;
			if (!open_quotes)
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
** Removes the quotes inside a single token.
** It takes nested quotes into account.
*/

static void	remove_quotes_single_token(t_token *token)
{
	size_t	i;
	size_t	idx;
	char	*removed_quotes_content;
	char	*inside_quotes;

	i = 0;
	idx = 0;
	removed_quotes_content = strdup_protect("");
	while (token->content[i])
	{
		if (token->content[i] == '\"' || token->content[i] == '\'')
		{
			idx = forward_quote_pair(token->content + i);
			inside_quotes = substr_protect(token->content + i + 1, 0, idx - 1);
			removed_quotes_content = join_protect(removed_quotes_content,
					inside_quotes);
			i += idx + 1;
			continue ;
		}
		removed_quotes_content = add_char_to_string(removed_quotes_content,
				token->content[i]);
		i++;
	}
	free(token->content);
	token->content = removed_quotes_content;
}

/*
** Remove quotes from the input.
** A token which contains empty quotes is not removed.
** Something like ls"" becomes ls.
*/

void	remove_quotes_from_all_tokens(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->content;
		if (token->type == WORD)
		{
			if (!strings_are_equal(token->content, "\"\"") && \
				!strings_are_equal(token->content, "\'\'"))
				remove_quotes_single_token(token_list->content);
		}
		token_list = token_list->next;
	}
}
