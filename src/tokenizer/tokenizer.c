/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/23 21:45:57 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
** Returns true when space is found, so we can continue in loop.
*/

static bool	take_correct_token(t_token **single_token, t_char_iter *itr)
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
		return (true);
	}
	else if (**itr == '&' || **itr == ';')
	{
		*single_token = create_token(*itr, 1, ERROR);
		next(itr);
	}
	else
		*single_token = take_word(itr);
	return (false);
}

t_list	*tokenize_input(char *input_string)
{
	t_list		*token_list;
	t_token		*single_token;
	t_char_iter	itr;
	bool		list_created;

	list_created = false;
	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		if (take_correct_token(&single_token, &itr))
			continue ;
		if (list_created == false)
		{
			token_list = ft_lstnew(single_token);
			list_created = true;
		}
		else
			ft_lstadd_back(&token_list, ft_lstnew(single_token));
	}
	return (token_list);
}
