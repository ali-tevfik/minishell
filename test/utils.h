/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/31 15:30:53 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>

/* Unity header */
#include "unity_fixture.h"

/* User defined header */
# include "../src/libft/libft.h"
# include "../src/parser/parser_data_structs.h"
# include "../src/tokenizer/tokenizer_data_structs.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_command	*create_command(t_redir_type redir_in, t_redir_type redir_out, 
							char *in_file, char *out_file, 
							size_t len_command, ...);
void	free_command(void *command);
void	compare_command_structs(t_command *expected_command, t_command *actual_command);
size_t	len_string_array(char **string_array);

#endif