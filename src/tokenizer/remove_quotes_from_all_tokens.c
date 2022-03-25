/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_from_all_tokens.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 10:21:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/25 14:52:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "remove_quotes_from_all_tokens.h"

static char	*string_is_null_handler(char c)
{
	char	*new_string;

	new_string = calloc_protect(2, sizeof(*new_string));
	new_string[0] = c;
	new_string[1] = '\0';
	return (new_string);
}

static char	*add_char_to_string(char *string, char c)
{
	size_t	len;
	char	*new_string;

	if (string == NULL)
		return (string_is_null_handler(c));
	len = ft_strlen(string);
	new_string = calloc_protect(len + 2, sizeof(*new_string));
	ft_memmove(new_string, string, len);
	new_string[len] = c;
	new_string[len + 1] = '\0';
	return (new_string);
}

/*
** Return the new string appended with the empty quotes.
** Also moves i.
** If it wasn't empty quotes, it returns NULL.
*/

bool	empty_quotes_found(char **removed_quotes_content, char *content, size_t *i)
{
	if (content[*i] == content[*i + 1])
	{
		*removed_quotes_content = add_char_to_string(*removed_quotes_content, content[*i]);
		*i = *i + 1;
		return (true);
	}
	return (false);
}

static void	remove_quotes_single_token(t_token *token)
{
	size_t	i;
	char	*removed_quotes_content;
	bool	dquote_active;
	bool	squote_active;

	i = 0;
	removed_quotes_content = NULL;
	dquote_active = false;
	squote_active = false;
	while (token->content[i])
	{
		if (token->content[i] && (token->content[i] == '\"' || \
			token->content[i] == '\''))
		{
			// If no empty quote found, we can skip it (not adding to content)
			if (!empty_quotes_found(&removed_quotes_content, token->content, &i))
			{
				i++;
				continue ;
			}
		}
		removed_quotes_content = add_char_to_string(removed_quotes_content,
				token->content[i]);
		i++;
	}
	free(token->content);
	token->content = removed_quotes_content;
}

void	remove_quotes_from_all_tokens(t_list *token_list)
{
	while (token_list)
	{
		if (((t_token *)(token_list->content))->type == WORD)
			remove_quotes_single_token(token_list->content);
		token_list = token_list->next;
	}
}
