/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_signals.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:09:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 14:14:26 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "set_signals.h"

void	set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
