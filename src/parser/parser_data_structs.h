/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_data_structs.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:44:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/04 12:03:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DATA_STRUCTS_H
# define PARSER_DATA_STRUCTS_H

/* System headers */

/* User defined headers */
# include "../libft/libft.h"

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

/* Data struct for redirection */
typedef struct s_redirection
{
	char			*file;
	t_redir_type	redir_type;
}				t_redirection;

/* 
** Data struct for storing all information 
** needed for a process to execute a command.
*/
typedef struct s_pipeline
{
	char	**command;
	t_list	*redirection;
}				t_pipeline;

/* Data struct for handling the looping over the tokens (until pipes) */
typedef struct s_list_location
{
	size_t	list_idx;
	t_list	*head;
}				t_list_location;

#endif
