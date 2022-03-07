/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/07 13:56:44 by hyilmaz       ########   odam.nl         */
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

extern int g_interactive;

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
	// if (match_str(pipeline->command[0], "cd") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "pwd") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "exit") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "echo") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "env") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "export") == 0)
	// 	i = 1;
	// else if (match_str(pipeline->command[0], "unset") == 0)
	// 	i = 1;
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
	// if (match_str(pipeline->command[0], "cd") == 0)
	// 	cd_command(pipeline->command[1], *env);
	// else if (match_str(pipeline->command[0], "pwd") == 0)
	// 	pwd_command(pipeline);
	// else if (match_str(pipeline->command[0], "exit") == 0)
	// 	exit_command(pipeline->command[1]);
	// else if (match_str(pipeline->command[0], "echo") == 0)
	// 	echo_command(pipeline);
	// else if (match_str(pipeline->command[0], "env") == 0)
	// 	env_command(*env);
	// else if (match_str(pipeline->command[0], "export") == 0)
	// 	export_command(env, pipeline);
	// else if (match_str(pipeline->command[0], "unset") == 0)
	// 	unset_command(env, pipeline);
	if (strings_are_equal(pipeline->command[0], "cd"))
		cd_command(pipeline->command[1], *env);
	else if (strings_are_equal(pipeline->command[0], "pwd"))
		pwd_command(pipeline);
	else if (strings_are_equal(pipeline->command[0], "exit"))
		exit_command(pipeline->command[1]);
	else if (strings_are_equal(pipeline->command[0], "echo"))
		echo_command(pipeline);
	else if (strings_are_equal(pipeline->command[0], "env"))
		env_command(*env);
	else if (strings_are_equal(pipeline->command[0], "export"))
		export_command(env, pipeline);
	else if (strings_are_equal(pipeline->command[0], "unset"))
		unset_command(env, pipeline);
	return (0);
}

int	tokenize_parse_execute(char *line, t_list **env)
{
	t_list		*lst;
	t_list		*pipe_lst;
	t_pipeline	*pipeline;

	lst = tokenize_input(line);
	if (lst == NULL)	/* when -c option and empty string passed */
		return (0);
	if (!validate_grammer(lst))
		return (-1);
	remove_quotes_from_all_tokens(lst);
	pipe_lst = create_parse_list(lst);
	pipeline = pipe_lst->content;
	if (built_in_and_infile_check(pipeline, pipe_lst))
		return (work_execve(pipe_lst, env));
	else if (is_builtin(pipeline))
		return (execute_builtin(pipeline, env));
	return (work_execve(pipe_lst, env));
}
