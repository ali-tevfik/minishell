/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:50:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 16:17:56 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

/* System headers */
# include <stdio.h>
# include <stdbool.h>

/* User defined header */
# include "../libft/libft.h"
# include "tokenizer_data_structs.h"
# include "iterator_api.h"

/* Data structures */

/* Function prototypes */
bool	is_char_a_delimiter(char c);
t_token	*create_token(char *content, size_t len_content, t_token_type type);
int		ft_isspace(int c);
void	print_token(t_token *token);
void	print_token_list(t_list *token_list);

#endif 