/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/02/23 20:15:33 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

#include "parser/create_parse_list.h"
#include "tokenizer/tokenizer.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	env = add_envp(envp);
	(void)argc;
	if (match_str(argv[1], "-c") == 0)
		test_working(argv, &env);
	while (1)
	{
		line = readline("Minishell> ");
		if ('-' == line[0] && '1' == line[1])
			break ;
		if (match_str(line, "") != 0)
		{
			add_history(line);
			line = check_expander(line, env);
			printf("retrun line %s\n", line);
			line_(line, &env);
		}
		free(line);
	}
	free(line);
	return (0);
}
