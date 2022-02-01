/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_parse_list.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:00:30 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 18:18:09 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_PARSE_LIST_H
# define CREATE_PARSE_LIST_H

/* System headers */
# include <stdio.h>

/* User defined header */
# include "../libft/libft.h"
# include "parser_data_structs.h"
# include "create_simple_command.h"

/* Macros */

/* Data structures */

/* Function prototypes */
t_list	*create_parse_list(t_list *token_list);

#endif