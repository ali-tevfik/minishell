/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 15:29:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "tokenizer_utils.h"
# include "iterator_api.h"

/* Data structures */

/* Function prototypes */
t_list	*tokenize_input(char *input_string);

#endif