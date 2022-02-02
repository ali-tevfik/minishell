/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_data_structs.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:44:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/02 14:40:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DATA_STRUCTS_H
# define PARSER_DATA_STRUCTS_H

/* System headers */

/* Data structures for the parser */
/* NONE means no redirection operator */
typedef enum e_redir_type
{
	OUT,
	APPEND,
	READ,
	HERE_DOC,
	NONE
}	t_redir_type;

typedef struct s_command
{
	char			**command;
	char			*in_file;
	char			*out_file;
	t_redir_type	redirection_operator_in;
	t_redir_type	redirection_operator_out;
}				t_command;

typedef struct s_list_location
{
	size_t	list_idx;
	t_list	*head;
}				t_list_location;

#endif
