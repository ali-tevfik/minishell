/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/24 20:34:43 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

/* System headers */
# include <stdio.h>

/* User defined header */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_data_structs.h"
# include "parser_data_structs.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_command	*create_simple_command_up_until_pipe_token(t_list *token_list, \
														size_t *location);

#endif