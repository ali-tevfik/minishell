/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 14:23:42 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/10 18:56:28 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

char *write_expander(char *str, t_list *env)
{
	char *txt;
	int	i;
	char *bigtxt;
	int	len;
	int	y;

	y = 0;
	i = 0;
	while(str[i] != '$')
		i++;
	txt = expander((str + i + 1), env);
	if (!txt)
		return (ft_strdup(""));
	len = i + ft_strlen(txt);
	bigtxt = (char *)malloc(sizeof(bigtxt) * (len + 1));
	if (!bigtxt)
		exit(1);
	i = 0;
	while(str[i] != '$')
	{
		bigtxt[i] = str[i];
		i++;
	}
	while(txt[y])
	{
		bigtxt[i + y] = txt[y];
		y++;
	}
	bigtxt[i + y] = '\0';
	free(str);
	return (bigtxt);
}

void	echo_command(t_pipeline *pipe_line, t_list *env)
{
	int	i;
	int	new_line;
	int	x;

	i = 0;
	new_line = 0;
	i = 1;
	if (ft_strncmp(pipe_line->command[1], "-n", 2) == 0)
		new_line = 1;

	while (pipe_line->command[i])
	{
		if (ft_strrchr(pipe_line->command[i], '$') != 0)
			pipe_line->command[i] = write_expander(pipe_line->command[i], env);
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
