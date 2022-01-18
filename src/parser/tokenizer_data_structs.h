/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_data_structs.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:26:35 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 15:29:20 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_DATA_STRUCTS_H
# define TOKENIZER_DATA_STRUCTS_H

/* Data structures for the tokenizer */
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

#endif