/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_pipe.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:18:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:16:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_pipe.h"

t_token	*take_pipe(t_char_iter *itr)
{
	t_token	*token;

	token = create_token(*itr, 1, PIPE);
	next(itr);
	return (token);
}
