/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:13:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/31 14:14:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_COMMAND_H
# define FIND_COMMAND_H

/* System headers */
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>

/* User defined header */
# include "../libft/libft.h"
# include "../parser/parser_data_structs.h"

/* Macros */

/* Data structures */

/* Function prototypes */
bool	find_command(t_command *command);

#endif