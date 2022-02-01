/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 16:18:26 by hyilmaz       ########   odam.nl         */
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
t_command	*init_command(t_list *token_list);
size_t		number_command_tokens(t_list *token_list);

#endif