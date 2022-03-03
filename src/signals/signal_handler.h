/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:06:51 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/03 13:18:44 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

/* Global variable */
extern int g_interactive;

/* System headers */
# include <stdio.h>
# include <readline/readline.h>

/* User defined header */
# include "../libft/libft.h"

/* Function prototypes */
void	sig_handler(int signum);

#endif