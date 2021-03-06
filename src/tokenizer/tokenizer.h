/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 15:41:18 by hyilmaz       ########   odam.nl         */
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
# include "tokenize_redirection.h"
# include "../../incl/protect.h"

/* Macros */
# define SUCCESS 0
# define BLANK_SPACE 1
# define MALLOC_FAILURE 2

/* Data structures */

/* Function prototypes */
t_list	*tokenize_input(char *input_string, t_list *env, int exitcode);

#endif
