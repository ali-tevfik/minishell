/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_quotes.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:34:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 18:16:30 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_QUOTES_H
# define TOKENIZE_QUOTES_H

/* System headers */

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"

/* Data structures */

/* Function prototypes */
t_token	*take_single_quotes(t_char_iter *itr);

#endif