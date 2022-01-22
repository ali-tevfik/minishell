/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/22 22:19:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "tokenizer_utils.h"
# include "iterator_api.h"
# include "tokenize_word.h"
# include "tokenize_pipe.h"
# include "tokenize_quotes.h"
# include "tokenize_dquotes.h"
# include "tokenize_redirection.h"

/* Data structures */

/* Function prototypes */
t_list	*tokenize_input(char *input_string);

#endif