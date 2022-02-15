/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/02/15 16:08:37 by adoner        ########   odam.nl         */
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
	argc = 1;
	argv = NULL;
	while (1)
	{
		line = readline("> ");
		if ('-' == line[0] && '1' == line[1])
			break ;
		if (ft_strncmp(line, "", 1) != 0)
		{
			add_history(line);
			line_(line, &env);
		}
		free(line);
	}
	free(line);
	return (0);
}
