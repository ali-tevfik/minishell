/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_api.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 12:52:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 13:46:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_api.h"
#include <stdio.h>

/* Check whether there are elements left to consume in the iterator */
bool	has_next(t_char_iter itr)
{
	return (*itr != '\0' && *itr != '\n');
}

/* Peek at the value inside of the iterator without consuming it */
char	peek(t_char_iter itr)
{
	return (*itr);
}

/* Consume one element of iterator and continue */
char	next(t_char_iter *itr)
{
	char	current;

	current = **itr;
	(*itr)++;
	return (current);
}
