/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 18:31:30 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>

/* Unity header */
#include "unity_fixture.h"

/* User defined header */
# include "../src/parser/parser_data_structs.h"

/* Macros */

/* Data structures */

/* Function prototypes */
void	compare_command_structs(t_command *expected_command, t_command *actual_command);
size_t	len_string_array(char **string_array);

#endif