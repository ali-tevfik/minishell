/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 14:05:06 by adoner        ########   odam.nl         */
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

extern int	g_interactive;

int	work_execve(t_list *pipe_lst, t_list **env)
{
	int	last_id;
	int	last_process_exit_status;

	last_id = 0;
	fork_func(pipe_lst, *env, &last_id);
	last_process_exit_status = wait_and_get_last_exit_status(last_id);
	g_interactive = 1;
	return (last_process_exit_status);
}

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
		echo_command(pipeline);
	else if (strings_are_equal(pipeline->command[0], "env"))
		env_command(*env);
	else if (strings_are_equal(pipeline->command[0], "export"))
		exit_code = export_command(env, pipeline);
	else if (strings_are_equal(pipeline->command[0], "unset"))
		exit_code = unset_command(env, pipeline);
	return (exit_code);
}

int	tokenize_parse_execute(char *line, t_list **env, int exit_code)
{
	t_list		*lst;
	t_list		*pipe_lst;
	t_pipeline	*pipeline;

	lst = tokenize_input(line, *env, exit_code);
	if (lst == NULL)
		return (0);
	if (!validate_grammer(lst))
		return (-1);
	remove_quotes_from_all_tokens(lst);
	pipe_lst = create_parse_list(lst);
	read_here_doc(pipe_lst);
	pipeline = pipe_lst->content;
	if (built_in_and_infile_check(pipeline, pipe_lst))
		return (work_execve(pipe_lst, env));
	else if (is_builtin(pipeline))
		return (execute_builtin(pipeline, env));
	return (work_execve(pipe_lst, env));
}
