/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/02 16:59:48 by hyilmaz       ########   odam.nl         */
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
#include <stdbool.h>

extern int g_interactive;

void	work_execve(t_list *pipe_lst, t_list **env)
{
	int	last_id;

	last_id = 0;
	fork_func(pipe_lst, *env, &last_id);
	wait_and_get_last_exit_status(last_id);
	g_interactive = 1;
}

int	check_built_in_file(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (match_str(pipeline->command[0], "cd") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "pwd") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "exit") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "echo") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "env") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "export") == 0)
		i = 1;
	else if (match_str(pipeline->command[0], "unset") == 0)
		i = 1;
	return (i);
}

static bool built_in_and_infile_check(t_list *pipe_lst)
{
	t_pipeline	*pipeline;

	pipeline = pipe_lst->content;
	if (pipeline->redirection || pipe_lst->next)
	{
		if (check_built_in_file(pipeline))
			return (true);
	}
	return (false);
}

void	built_in(t_pipeline *pipeline, t_list **env)
{
	if (match_str(pipeline->command[0], "cd") == 0)
		cd_command(pipeline->command[1], *env);
	else if (match_str(pipeline->command[0], "pwd") == 0) 	/* prints data */
		pwd_command(pipeline);
	else if (match_str(pipeline->command[0], "exit") == 0)
		exit_command(pipeline->command[1]);
	else if (match_str(pipeline->command[0], "echo") == 0) 	/* prints data */
		echo_command(pipeline);
	else if (match_str(pipeline->command[0], "env") == 0) 	/* prints data */
		env_commands(*env);
	else if (match_str(pipeline->command[0], "export") == 0)
		export_command(env, pipeline);
	else if (match_str(pipeline->command[0], "unset") == 0)
		unset_command(env, pipeline);
}

void	line_(char *line, t_list **env)
{
	t_list		*token_list;
	t_list		*pipe_list;

	token_list = tokenize_input(line);
	if (!validate_grammer(token_list))
		return ;
	remove_quotes_from_all_tokens(token_list);
	pipe_list = create_parse_list(token_list);
	if (built_in_and_infile_check(pipe_list))		/* If list more than 1 element or redirection present */
		work_execve(pipe_list, env);
	else if (check_built_in_file(pipe_list->content))
		built_in(pipe_list->content, env);
	else
		work_execve(pipe_list, env);
}
