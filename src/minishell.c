/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/02/28 16:30:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

#include "parser/create_parse_list.h"
#include "tokenizer/tokenizer.h"
#include <signal.h>

int	g_pid;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	signal(SIGINT, sig_handler);
	env = add_envp(envp);
	(void)argc;
	if (match_str(argv[1], "-c") == 0)
		test_working(argv, &env);
	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
		{
			return (1);
		}
		if (match_str(line, "") != 0)
		{
			add_history(line);
			line = check_expander(line, env);
			line_(line, &env);
		}
		free(line);
	}
	free(line);
	return (0);
}
