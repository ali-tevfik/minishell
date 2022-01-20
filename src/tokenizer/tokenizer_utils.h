/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:50:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 15:44:02 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

/* System headers */
# include <stdio.h>
# include <stdbool.h>

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "iterator_api.h"

/* Data structures */

/* Function prototypes */
bool	is_char_a_delimiter(char c);
t_token	*create_token(char *content, size_t len_content, t_token_type type);
t_token	*take_redirection(t_char_iter *itr);
t_token	*take_double_quotes(t_char_iter *itr);

#endif 