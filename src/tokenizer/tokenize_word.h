/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_word.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:36:13 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 14:54:32 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_WORD_H
# define TOKENIZE_WORD_H

/* System headers */

/* User defined header */
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"
# include "../../incl/minishell.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_token	*take_word(t_char_iter *itr,  t_list *env, int exitcode);

#endif
