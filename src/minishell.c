/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/01/25 18:37:56 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	line_(char *line, t_list *env)
{
	if (ft_strncmp(line, "cd ", 3) == 0)
		cd_command(line);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		pwd_command();
	else if (ft_strncmp(line, "exit", 4) == 0)
		exit (0);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		echo_command(line);
	else if (ft_strncmp(line, "env", 3) == 0)
		env_commands(env);
	else if (ft_strncmp(line, "export ", 7) == 0)
		export_command(env, line);
	else if (ft_strncmp(line, "unset ", 6) == 0)
		unset_command(env, line);
	else if (ft_strncmp(line, "", 1) != 0)
		printf("bash: %s: command not found\n", line);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	env = add_envp(envp);
	argc = 1;
	argv = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, "", 1) != 0)
			add_history(line);
		if ('-' == line[0] && '1' == line[1])
			break ;
		line_(line, env);
		free(line);
	}
	free(line);
	return (0);
}
