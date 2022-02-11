/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/11 19:13:39 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "parser/parser_data_structs.h"
#include "parser/create_simple_command.h"
#include "tokenizer/tokenizer.h"
#include "../incl/fork.h"
#include "parser/create_parse_list.h"

void	work_execve(t_list *pipe_lst, t_list *env)
{
	int	last_id;

	last_id = 0;
	fork_func(pipe_lst, env, &last_id);
	wait_and_get_last_exit_status(last_id);
}

void	line_(char *line, t_list **env)
{
	t_list		*lst;
	t_list		*pipe_lst;
	t_pipeline	*pipeline;

	lst = tokenize_input(line);
	pipe_lst = create_parse_list(lst);
	pipeline = pipe_lst->content;
	if (match_str(pipeline->command[0], "cd") == 0)
		cd_command(pipeline->command[1], *env);
	else if (match_str(pipeline->command[0], "pwd") == 0)
		pwd_command(pipeline);
	else if (match_str(pipeline->command[0], "exit") == 0)
		exit (0);
	else if (match_str(pipeline->command[0], "echo") == 0)
		echo_command(pipeline);
	else if (match_str(pipeline->command[0], "env") == 0)
		env_commands(*env);
	else if (match_str(pipeline->command[0], "export") == 0)
		export_command(env, pipeline);
	else if (match_str(pipeline->command[0], "unset") == 0)
		unset_command(env, pipeline);
	else
		work_execve(pipe_lst, *env);
}
