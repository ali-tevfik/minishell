/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 12:37:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/04/01 12:56:27 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/errno.h>
#include <string.h>

void	print_error(char *command, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (text == NULL)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}
