/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:40:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 18:17:39 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
		if (*itr == '|')
			single_token = take_pipe(&itr);
		else if (*itr == '<' || *itr == '>')
			single_token = take_redirection(&itr);
		else if (*itr == '\'')
			single_token = take_single_quotes(&itr);
		else if (*itr == '\"')
			single_token = take_single_quotes(&itr);
		else if (ft_isspace(*itr) == 1)
		{
			next(&itr);
			continue ;
		}
		else
			single_token = take_word(&itr);
*/

t_list	*tokenize_input(char *input_string)
{
	t_list		*token_list;
	t_token		*single_token;
	t_char_iter	itr;
	int			i;

	i = 0;
	token_list = NULL;
	itr = input_string;
	while (has_next(itr))
	{
		if (i == 0)
			token_list = ft_lstnew(single_token);
		else
			ft_lstadd_back(&token_list, ft_lstnew(single_token));
		i++;
	}
	return (token_list);
}
