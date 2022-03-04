/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/03/04 12:30:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "parser/create_parse_list.h"
#include "tokenizer/tokenizer.h"
#include "signals/set_signals.h"

/* 
** Makes sure that signal is handled by either child or parent process, 
** not both.
*/

int	g_interactive = 1;

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
	char			*expanded_line;
	unsigned char	last_exit_status;
	t_list			*env_list;

	env_list = init_shell(argc, argv, envp, &last_exit_status);
	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (0);
		// if (match_str(line, "") != 0)
		// {
		// 	add_history(line);
		// 	line = check_expander(line, env_list);
		// 	last_exit_status = line_(line, &env_list);
		// 	printf("last exit status = %d\n", last_exit_status);
		// }
		if (!strings_are_equal(line, ""))
		{
			add_history(line);
			expanded_line = expand_input_string(line, env_list);
			last_exit_status = tokenize_parse_execute(expanded_line, &env_list);
			printf("last exit status = %d\n", last_exit_status);
		}
		free(line);
	}
	free(line);
	return (0);
}
