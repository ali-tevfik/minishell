/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:06:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/25 11:45:23 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

/*
** g_interactive == 1 --> we are in idle mode (no commands are executing).
** g_interactive == 2 --> we are in here doc handling.
*/

void	sig_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 2);
	if (g_interactive == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
