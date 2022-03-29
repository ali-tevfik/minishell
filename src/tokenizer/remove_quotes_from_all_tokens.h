/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_from_all_tokens.h                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 10:22:00 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/29 12:36:02 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_QUOTES_FROM_ALL_TOKENS_H
# define REMOVE_QUOTES_FROM_ALL_TOKENS_H

/* System headers */

/* User defined header */
# include "tokenizer_data_structs.h"
# include "iterator_api.h"
# include "tokenizer_utils.h"
# include "../../incl/protect.h"
# include "../../incl/built_in.h"

/* Macros */

/* Data structures */

/* Function prototypes */
void	remove_quotes_from_all_tokens(t_list *token_list);
int		forward_quote_pair(char *line);

#endif