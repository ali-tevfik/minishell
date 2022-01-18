/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_api.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 12:52:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 13:46:53 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_API_H
# define ITERATOR_API_H

/* System headers */
# include <stdbool.h>

/* User defined header */

/* Definitions */
typedef char*	t_char_iter;

/* Data structures */

/* Function prototypes */
bool	has_next(t_char_iter itr);
char	next(t_char_iter *itr);

#endif