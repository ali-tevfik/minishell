/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/24 15:26:15 by adoner        ########   odam.nl         */
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

void	work_execve(t_list *pipe_lst, t_list **env)
{
	int	last_id;

	last_id = 0;
	fork_func(pipe_lst, *env, &last_id);
	wait_and_get_last_exit_status(last_id);
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

int	built_in_and_infile_check(t_pipeline *pipeline, t_list *pipe_lst)
{
	if (pipeline->redirection || pipe_lst->next)
	{
		if (check_built_in_file(pipeline))
			return (1);
	}
	return (0);
}

void	built_in(t_pipeline *pipeline, t_list **env)
{
	if (match_str(pipeline->command[0], "cd") == 0)
		cd_command(pipeline->command[1], *env);
	else if (match_str(pipeline->command[0], "pwd") == 0)
		pwd_command(pipeline);
	else if (match_str(pipeline->command[0], "exit") == 0)
		exit_command(pipeline->command[1]);
	else if (match_str(pipeline->command[0], "echo") == 0)
		echo_command(pipeline);
	else if (match_str(pipeline->command[0], "env") == 0)
		env_commands(*env);
	else if (match_str(pipeline->command[0], "export") == 0)
		export_command(env, pipeline);
	else if (match_str(pipeline->command[0], "unset") == 0)
		unset_command(env, pipeline);
}

void	line_(char *line, t_list **env)
{
	t_list		*lst;
	t_list		*pipe_lst;
	t_pipeline	*pipeline;

	lst = tokenize_input(line);
	if (!validate_grammer(lst))
		return ;
	remove_quotes_from_all_tokens(lst);
	pipe_lst = create_parse_list(lst);
	if (pipe_lst){
		pipeline = pipe_lst->content;}
	else
		return ;
	if (built_in_and_infile_check(pipeline, pipe_lst))
		work_execve(pipe_lst, env);
	else if (check_built_in_file(pipeline))
		built_in(pipeline, env);
	else
		work_execve(pipe_lst, env);
}
