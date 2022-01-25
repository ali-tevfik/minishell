/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_dquotes.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:06:37 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:08:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_DQUOTES_H
# define TOKENIZE_DQUOTES_H

/* System headers */

/* User defined header */
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_token	*take_double_quotes(t_char_iter *itr);

#endif