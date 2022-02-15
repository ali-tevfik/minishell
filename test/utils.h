/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/15 13:25:28 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>

/* Unity header */
#include "unity_fixture.h"

/* User defined header */
# include "../src/libft/libft.h"
# include "../src/parser/parser_data_structs.h"
# include "../src/tokenizer/tokenizer_data_structs.h"
# include "../incl/commands.h"

/* Macros */

/* Data structures */

/* Function prototypes */
char			**create_command(size_t len_command, ...);
t_list			*create_redirection_list(size_t total_redir_operators_plus_filenames, ...);
t_pipeline		*create_pipeline_element(char **command, t_list *redirection);
void			free_pipeline(void *pipeline);
void			free_command(char **command);
void			compare_pipelines(t_pipeline *expected_pipeline, t_pipeline *actual_pipeline);
size_t			len_string_array(char **string_array);
void			print_string_array(char **string_array);
t_list			*copy_environment_linked_list(t_list *env_list);
void			compare_environment_lists(t_list *expected_env_list, t_list *actual_env_list);
t_env			*create_env_variable(char *key, char *value);
void			free_env_variable(void *environment_variable);
t_list			*create_environment_list(int len, ...);

#endif