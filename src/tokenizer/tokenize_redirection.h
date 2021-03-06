/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_redirection.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:45:54 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 11:20:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_REDIRECTION_H
# define TOKENIZE_REDIRECTION_H

/* System headers */

/* User defined header */
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_token	*take_redirection(t_char_iter *itr);

#endif