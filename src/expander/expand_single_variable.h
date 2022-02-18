/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_single_variable.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 18:56:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/18 13:46:43 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_SINGLE_VARIABLE_H
# define EXPAND_SINGLE_VARIABLE_H

/* System headers */
# include <stdio.h>
# include <stdbool.h>

/* User defined header */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_utils.h"
# include "../../incl/built_in.h"


/* Macros */


/* Data structures */

/* Function prototypes */
char	*expand_single_variable(t_list *env, char *string, size_t n);

#endif