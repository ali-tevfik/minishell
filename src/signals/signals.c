/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 11:35:45 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/09 12:04:50 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	signal_handles(int signum)
{
	if (signum == SIGINT)
		printf("Caught SIGINT\n");
	else if (signum == SIGQUIT)
		printf("Caught SIGQUIT\n");
	else if (signum == SIG)
}