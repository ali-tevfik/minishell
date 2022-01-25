/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_data_structs.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:26:35 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/22 18:00:12 by hyilmaz       ########   odam.nl         */
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
	REDIRECTION,
	QUOTE,
	DQUOTE
}				t_token_type;

typedef struct s_token
{
	char			*content;
	size_t			len_content;
	t_token_type	type;
}				t_token;

#endif