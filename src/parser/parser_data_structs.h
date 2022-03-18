/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_data_structs.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:44:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 15:38:41 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DATA_STRUCTS_H
# define PARSER_DATA_STRUCTS_H

/* System headers */

/* User defined headers */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_data_structs.h"

/* Data struct for redirection */
typedef struct s_redirection
{
	char			*file;
	t_token_type	redir_type;
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
