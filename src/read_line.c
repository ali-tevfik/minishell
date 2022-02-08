/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 14:26:14 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
** pwdaa works like pwd
**
**
*/

void	line_(char *line, t_list **env)
{
	if (ft_strncmp(line, "cd ", 3) == 0)
		cd_command(line);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		pwd_command();
	else if (ft_strncmp(line, "exit", 4) == 0)
		exit (0);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		echo_command(line+5);
	else if (ft_strncmp(line, "env", 3) == 0)
		env_commands(*env);
	else if (ft_strncmp(line, "export ", 7) == 0)
		export_command(env, line);
	else if (ft_strncmp(line, "unset ", 6) == 0)
		unset_command(env, line);
	else if (ft_strncmp(line, "", 1) != 0)
		printf("bash: %s: command not found\n", line);
}
