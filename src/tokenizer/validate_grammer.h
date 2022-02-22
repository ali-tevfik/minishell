/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_grammer.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:18:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 19:01:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_GRAMMER_H
# define VALIDATE_GRAMMER_H

/* System headers */
# include <stdbool.h>
# include <stdio.h>

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "iterator_api.h"

/* Macros */

/* Data structures */

/* Function prototypes */
bool	is_redirection(t_token_type type);
bool	validate_grammer(t_list *token_list);

#endif