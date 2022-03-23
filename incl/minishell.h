/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:21:43 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 18:57:17 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/libft.h"
# include "built_in.h" /* Circular includes */
# include <sys/types.h>
# include <fcntl.h>

int		tokenize_parse_execute(char *line, t_list **env, int exit_code);
char	**create_envp(t_list *env_lst);
void	test_working(char *argv[], t_list **env);
char	*expand_input_string(char *line, t_list *env, int exit_code);
#endif
