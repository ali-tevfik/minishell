/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_simple_command.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:11:04 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 16:19:05 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_SIMPLE_COMMAND_H
# define CREATE_SIMPLE_COMMAND_H

/* System headers */
# include <stdio.h>
# include <stdbool.h>

/* User defined header */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_data_structs.h"
# include "parser_data_structs.h"
# include "parser_utils.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_command	*create_simple_command_up_until_pipe_token(t_list *token_list, \
														size_t *location);

#endif