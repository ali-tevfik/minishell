/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:21:43 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/19 14:53:15 by hyilmaz       ########   odam.nl         */
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

void	line_(char *line, t_list **env);
char	**create_envp(t_list *env_lst);

#endif
