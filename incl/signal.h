/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 17:06:49 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/17 17:14:53 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "minishell.h"

void	signal_int(int sig);
void	signal_quick(int sig);
void	signal_no_finish(int sig);
void	control_d(void);

#endif
