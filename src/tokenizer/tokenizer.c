/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/19 23:16:46 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_list	*tokenize_input(char *input_string)
{
	t_list		*token_list;
	t_token		*token;
	t_char_iter	itr;
	int			i;

	i = 0;
	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		if (*itr == '|')
			;
		else
		{
			token = take_word(&itr);
		}
		if (i == 0)
			token_list = ft_lstnew(token);
		else
			ft_lstadd_back(&token_list, ft_lstnew(token));
	}
	return (token_list);
}
