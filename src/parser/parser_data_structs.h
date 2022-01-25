/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_data_structs.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:44:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/25 11:30:15 by hyilmaz       ########   odam.nl         */
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
	char			*filename;
	t_redir_type	redirection_operator;
}				t_command;

typedef struct s_pipeline
{
	struct s_pipeline	*pipeline;
	t_command			*command;
}				t_pipeline;

#endif