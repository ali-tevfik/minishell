/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/28 13:29:48 by hyilmaz       ########   odam.nl         */
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
	int			exit_status;

	lst = tokenize_input(line, *env, exit_code);
	if (lst == NULL)
		return (0);
	// print_token_list(lst);
	if (!validate_grammer(lst))
		return (-1);
	remove_quotes_from_all_tokens(lst);
	pipe_lst = create_parse_list(lst);
	// print_commands(pipe_lst);
	if (!read_here_doc(pipe_lst))
		return (-1);
	pipeline = pipe_lst->content;
	if (!pipeline->command[0])
		return (0);
	if (built_in_and_infile_check(pipeline, pipe_lst))
		exit_status = work_execve(pipe_lst, env);
	else if (is_builtin(pipeline))
		exit_status = execute_builtin(pipeline, env);
	else
		exit_status = work_execve(pipe_lst, env);
	ft_lstclear(&pipe_lst, free_parse_list_element);
	ft_lstclear(&lst, free_token);
	// free(line);3
	return (exit_status);
}
