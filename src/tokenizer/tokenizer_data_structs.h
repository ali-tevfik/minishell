/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_data_structs.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:26:35 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 11:36:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_DATA_STRUCTS_H
# define TOKENIZER_DATA_STRUCTS_H

/* System headers */
# include <stddef.h>

/* Data structures for the tokenizer */
typedef enum e_token_type
{
	ERROR = -1,
	WORD,
	PIPE,
	WRITE,
	APPEND,
	READ,
	HERE_DOC,
	QUOTE,
	DQUOTE,
	AMPERSAND,
	SEMICOLON,
}				t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
}				t_token;

#endif