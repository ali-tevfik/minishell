/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 14:03:28 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/17 17:14:37 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/signal.h"

/*
//	rl_on_new_line();
//	rl_redisplay();
 */
void	signal_int(int sig)
{
	if (sig == SIGINT)
		printf("sigint = %d\n", sig);
	if (sig == SIGQUIT)
		printf("sigquit = %d\n", sig);
}

void	signal_no_finish(int sig)
{
	printf("je kan niet uit! %d \n", sig);
}

void	signal_quick(int sig)
{
	printf("1! %d \n", sig);
	rl_on_new_line();
	rl_redisplay();
}

void	control_d(void)
{
	ft_putstr_fd("exit\n", 2);
	exit (0);
}
