/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:13:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/02 15:57:30 by adoner        ########   odam.nl         */
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
// # define SUCCESS 0
// # define FAILURE 1
// # define MALLOC_FAIL 2
// # define NO_PATH 3
// # define COMMAND_NOT_FOUND 4

/* Data structures */

/* Function prototypes */
bool	find_command(t_command *command, t_list *lst);

#endif
