/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_pipe.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:18:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 15:32:53 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_PIPE_H
# define TOKENIZE_PIPE_H

/* System headers */

/* User defined header */
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_token	*take_pipe(t_char_iter *itr);

#endif