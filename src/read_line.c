/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 17:35:24 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "parser/parser_data_structs.h"
#include "parser/create_simple_command.h"
#include "tokenizer/tokenizer.h"
#include "../incl/fork.h"
#include "parser/create_parse_list.h"

/*
** pwdaa works like pwd
**
**
*/

void	line_(char *line, t_list **env)
{
	t_list *lst;
	t_list	*command;
	int	last_id;

	last_id = 0;
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
	else
	{
		lst = tokenize_input(line);
		command = create_parse_list(lst);
		fork_func(command, envp, *env, &last_id);
		wait_and_get_last_exit_status(last_id);
	}
}
