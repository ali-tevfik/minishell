/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:06:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/16 17:02:41 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	sig_handler(int signum)
{
	(void)signum;

	// rl_replace_line("", 0);
	ft_putchar_fd('\n', 2);
	if (g_interactive)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
