/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/29 12:33:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/29 12:35:35 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
#include "../parser/create_simple_command.h"
#include "../tokenizer/tokenizer.h"
#include "../../incl/fork.h"
#include "../parser/create_parse_list.h"
#include "../tokenizer/validate_grammer.h"
#include "../tokenizer/remove_quotes_from_all_tokens.h"
#include "../here_doc/handle_here_doc.h"

bool	is_builtin(t_pipeline *pipeline)
{
	bool	is_builtin;

	is_builtin = false;
	if (strings_are_equal(pipeline->command[0], "cd"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "pwd"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "exit"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "echo"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "env"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "export"))
		is_builtin = true;
	else if (strings_are_equal(pipeline->command[0], "unset"))
		is_builtin = true;
	return (is_builtin);
}

int	built_in_and_infile_check(t_pipeline *pipeline, t_list *pipe_lst)
{
	if (pipeline->redirection || pipe_lst->next)
	{
		if (is_builtin(pipeline))
			return (1);
	}
	return (0);
}

int	execute_builtin(t_pipeline *pipeline, t_list **env)
{
	int	exit_code;

	exit_code = 0;
	if (strings_are_equal(pipeline->command[0], "cd"))
		exit_code = cd_command(pipeline->command[1], *env);
	else if (strings_are_equal(pipeline->command[0], "pwd"))
		exit_code = pwd_command(pipeline);
	else if (strings_are_equal(pipeline->command[0], "exit"))
		exit_command(pipeline, &exit_code);
	else if (strings_are_equal(pipeline->command[0], "echo"))
		exit_code = echo_command(pipeline);
	else if (strings_are_equal(pipeline->command[0], "env"))
		exit_code = env_command(*env);
	else if (strings_are_equal(pipeline->command[0], "export"))
		exit_code = export_command(env, pipeline);
	else if (strings_are_equal(pipeline->command[0], "unset"))
		exit_code = unset_command(env, pipeline);
	return (exit_code);
}
