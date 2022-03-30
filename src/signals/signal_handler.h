/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:06:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/30 14:05:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

/* System headers */
# include <stdio.h>
# include <readline/readline.h>

/* User defined header */
# include "../libft/libft.h"

/* Global variable */
extern int	g_interactive;

/* Function prototypes */
void	sig_handler(int signum);

#endif