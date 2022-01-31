/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:21:43 by hyilmaz       #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/01/31 15:03:02 by adoner        ########   odam.nl         */
=======
/*   Updated: 2022/01/27 12:38:25 by hyilmaz       ########   odam.nl         */
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
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
# include "commands.h"

void	line_(char *line, t_list **env);

#endif
