/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 12:39:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>

/* User defined header */
# include "../libft/libft.h"

/* Data structures */
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_LEFT_ONCE,
	REDIR_LEFT_TWICE,
	REDIR_RIGHT_ONCE,
	REDIR_RIGHT_TWICE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ERROR,
}				t_token_type;

typedef struct s_token
{
	char			*content;
	size_t			len_content;
	t_token_type	type;
}				t_token;

/* Function prototypes */
t_list	*tokenize_input(char *input_string);

#endif