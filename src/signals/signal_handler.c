/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:06:25 by hyilmaz       #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/03/23 13:24:26 by hyilmaz       ########   odam.nl         */
=======
/*   Updated: 2022/03/23 16:03:29 by adoner        ########   odam.nl         */
>>>>>>> norm_check_adoner
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	sig_handler(int signum)
{
	(void)signum;
<<<<<<< HEAD

	rl_replace_line("", 0);
=======
	// rl_replace_line("", 0);
>>>>>>> norm_check_adoner
	ft_putchar_fd('\n', 2);
	if (g_interactive)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
