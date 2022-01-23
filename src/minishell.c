/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/01/20 15:12:17 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	argc = 1;
	argv = NULL;
	while (1)
	{
		line = readline("> ");
		if ('-' == line[0] && '1' == line[1])
			break ;
		add_history(line);
		if (ft_strncmp(line, "cd", 2) == 0)
		{
			cd_command(line);
		}
		else if (ft_strncmp(line, "pwd", 3) == 0)
			pwd_command();
		else if (ft_strncmp(line, "exit", 4) == 0)
			exit (0);
		else if (ft_strncmp(line, "echo", 4) == 0)
			echo_command(line);
		else if (ft_strncmp(line, "env", 3) == 0)
			env_commands(envp);
		free(line);
	}
	free(line);
	return (0);
}
