/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/03/23 18:49:26 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "parser/create_parse_list.h"
#include "tokenizer/tokenizer.h"
#include "signals/set_signals.h"

void	read_commands_from_string(int argc, char **argv,
			t_list **env, int exit_code);

/*
** Makes sure that signal is handled by either child or parent process,
** not both.
*/

int		g_interactive = 1;

/*
** Set signals and creates environment list.
** Each element of env_list contains a key-value pair.
*/

static t_list	*init_shell(int argc, char *argv[], char *envp[],
							unsigned char *last_exit_status)
{
	t_list	*env_list;

	set_signals();
	(void)argc;
	(void)argv;
	*last_exit_status = 0;
	env_list = create_env_list(envp);
	return (env_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	unsigned char	last_exit_status;
	t_list			*env_list;

	last_exit_status = 0;
	env_list = init_shell(argc, argv, envp, &last_exit_status);
	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (0);
		if (!strings_are_equal(line, ""))
		{
			add_history(line);
			last_exit_status = tokenize_parse_execute(line, &env_list,
					last_exit_status);
		}
		free(line);
	}
	free(line);
	return (0);
}
