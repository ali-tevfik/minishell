/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 12:38:15 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/fork.h"
#include "parser/create_parse_list.h"
#include "tokenizer/tokenizer.h"

void	line_(char *line, t_list **env, char *envp[])
{
	t_list	*tokenizer;
	t_list	*tokenizer_lst;
	int		id;

	tokenizer = tokenize_input(line);
	tokenizer_lst = create_parse_list(tokenizer);
	if (ft_strncmp(line, "cd ", 3) == 0)
		cd_command(line);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		pwd_command();
	else if (ft_strncmp(line, "exit", 4) == 0)
		exit (0);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		echo_command(line);
	else if (ft_strncmp(line, "env", 3) == 0)
		env_commands(*env);
	else if (ft_strncmp(line, "export ", 7) == 0)
		export_command(env, line);
	else if (ft_strncmp(line, "unset ", 6) == 0)
		unset_command(env, line);
	else
	{
		fork_func(tokenizer_lst, envp, *env, &id);
		wait_and_get_last_exit_status(id);
	}
}
