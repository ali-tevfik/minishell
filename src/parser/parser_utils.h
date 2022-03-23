/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 16:57:54 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>

/* User defined header */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_data_structs.h"
# include "../tokenizer/validate_grammer.h"
# include "parser_data_structs.h"
# include "../../incl/protect.h"

/* Macros */

/* Data structures */

/* Function prototypes */
void		free_parse_list_element(void *pipeline);
t_pipeline	*init_pipeline(t_list *token_list);

#endif