/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 17:24:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_list	*tokenize_input(char *input_string)
{
	t_list		*token_list;
	t_token		*token;
	t_char_iter	itr;

	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		if (*itr == '|')
			;
		else if (*itr == '>')
			;
		else if (*itr == '<')
			;
		else if (*itr == '\'')
			;
		else if (*itr == '\"')
			;
		else
		{
			token = take_word(&itr);
		}
	}
	return (token_list);
}
