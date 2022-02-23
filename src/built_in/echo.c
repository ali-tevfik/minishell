/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 14:23:42 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/23 19:35:09 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void	echo_command(t_pipeline *pipe_line)
{
	int	new_line;
	int	x;
	int	i;

	printf("echo insaa\n");
	new_line = 0;
	if (match_str(pipe_line->command[1], "-n") == 0)
		new_line = 1;
	i = 1;
	while (pipe_line->command[i])
	{
		x = 0;
		while (pipe_line->command[i][x])
		{
			if (pipe_line->command[i][x] != '"')
				ft_putchar_fd(pipe_line->command[i][x], 1);
			x++;
		}
		if (pipe_line->command[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line == 0)
		ft_putchar_fd('\n', 1);
}
