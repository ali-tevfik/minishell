/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 16:56:10 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_token	*take_other_tokens(t_char_iter *itr)
{
	t_token	*token;

	if (peek(*itr) == '&')
		token = create_token(NULL, AMPERSAND);
	else
		token = create_token(NULL, SEMICOLON);
	return (token);
}

/*
** Returns FAILURE when space is found, so we can continue in loop.
** Otherwise return SUCCES, or MALLOC_ERROR when an allocation failed.
*/

static size_t	take_correct_token(t_token **single_token, t_char_iter *itr, t_list *env, int exitcode)
{
	if (**itr == '|')
		*single_token = take_pipe(itr);
	else if (**itr == '<' || **itr == '>')
		*single_token = take_redirection(itr);
	else if (ft_isspace(**itr) == 1)
	{
		next(itr);
		return (BLANK_SPACE);
	}
	else if (**itr == '&' || **itr == ';')
	{
		*single_token = take_other_tokens(itr);
		next(itr);
	}
	else
		*single_token = take_word(itr, env, exitcode);
	return (SUCCESS);
}

/*
** Returns the list of tokens.
** If allocation fails, returns NULL.
*/

t_list	*tokenize_input(char *input_string, t_list *env, int exitcode)
{
	t_list		*token_list;
	t_list		*element;
	t_token		*single_token;
	t_char_iter	itr;
	size_t		ret;

	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		ret = take_correct_token(&single_token, &itr, env, exitcode);
		if (ret == BLANK_SPACE)
			continue ;
		else if (ret == MALLOC_FAILURE)
			return (NULL);
		element = lstnew_protect(single_token);
		ft_lstadd_back(&token_list, element);
	}
	return (token_list);
}
