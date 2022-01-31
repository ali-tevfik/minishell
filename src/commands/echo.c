/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 14:23:42 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/31 15:21:27 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	echo_command(char *text, t_list *env)
{
	int	i;
	int	new_line;

	new_line = 0;
	i = 5 + skip_space_start(text + 5);
	if (text[i] == '-')
	{
		if (text[i + 1] == 'n')
			new_line = 1;
		i += 2;
	}
	i += skip_space_start(text + i);
	while (text[i])
	{
		if (text[i] != '"')
		{
			if (text[i] == '$')
				i = expander(text + i, env) - 1;
			else
				ft_putchar_fd(text[i], 1);
		}
		i++;
	}
	if (new_line == 0)
		ft_putchar_fd('\n', 1);
}
