/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/25 13:40:18 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
** Returns FAILURE when space is found, so we can continue in loop.
** Otherwise return SUCCES, or MALLOC_ERROR when an allocation failed.
*/

static unsigned int	take_correct_token(t_token **single_token, t_char_iter *itr)
{
	if (**itr == '|')
		*single_token = take_pipe(itr);
	else if (**itr == '<' || **itr == '>')
		*single_token = take_redirection(itr);
	else if (**itr == '\'')
		*single_token = take_single_quotes(itr);
	else if (**itr == '\"')
		*single_token = take_double_quotes(itr);
	else if (ft_isspace(**itr) == 1)
	{
		next(itr);
		return (FAILURE);
	}
	else if (**itr == '&' || **itr == ';')
	{
		*single_token = create_token(*itr, 1, ERROR);
		next(itr);
	}
	else
		*single_token = take_word(itr);
	if (single_token == NULL)
		return (MALLOC_FAILURE);
	return (SUCCESS);
}

/*
** Returns the list of tokens.
** If allocation fails, returns NULL.
*/

t_list	*tokenize_input(char *input_string)
{
	t_list		*token_list;
	t_list		*element;
	t_token		*single_token;
	t_char_iter	itr;

	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		if (take_correct_token(&single_token, &itr) == FAILURE)
			continue ;
		element = ft_lstnew(single_token);
		if (element == NULL)
		{
			printf("Allocating memory for token_list failed.\n");
			return (NULL);
		}
		ft_lstadd_back(&token_list, element);
	}
	return (token_list);
}
