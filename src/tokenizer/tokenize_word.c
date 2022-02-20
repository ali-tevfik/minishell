/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_word.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:35:56 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 11:31:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_word.h"

t_token	*take_word(t_char_iter *itr)
{
	int		len;
	char	*start_token;
	char	*content;
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
	content = ft_substr(start_token, 0, len);
	if (content == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	token = create_token(content, WORD);
	return (token);
}
