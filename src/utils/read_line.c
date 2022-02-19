/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/19 00:19:36 by tevfik        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
#include "../parser/create_simple_command.h"
#include "../tokenizer/tokenizer.h"
#include "../../incl/fork.h"
#include "../parser/create_parse_list.h"
#include "../tokenizer/validate_grammer.h"

void work_execve(t_list *pipe_lst, t_list **env)
{
	int last_id;

	last_id = 0;
	fork_func(pipe_lst, *env, &last_id);
	wait_and_get_last_exit_status(last_id);
}

int check_built_in_file(t_pipeline *pipeline)
{
	int i;

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

int built_in_and_infile_check(t_pipeline *pipeline)
{
	if (pipeline->redirection)
	{
		if (check_built_in_file(pipeline))
			return (1);
	}
	return (0);
}

void built_in(t_pipeline *pipeline, t_list **env)
{
	if (match_str(pipeline->command[0], "cd") == 0)
		cd_command(pipeline->command[1], *env);
	else if (match_str(pipeline->command[0], "pwd") == 0)
		pwd_command(pipeline);
	else if (match_str(pipeline->command[0], "exit") == 0)
		exit(0);
	else if (match_str(pipeline->command[0], "echo") == 0)
		echo_command(pipeline);
	else if (match_str(pipeline->command[0], "env") == 0)
		env_commands(*env);
	else if (match_str(pipeline->command[0], "export") == 0)
		export_command(env, pipeline);
	else if (match_str(pipeline->command[0], "unset") == 0)
		unset_command(env, pipeline);
}

char *convert_dolar(char *command, t_list *env)
{
	char **parse_txt;
	int i;
	char *new_txt;
	i = 0;
	parse_txt = ft_split(command, '$');
	new_txt = NULL;
	while (parse_txt[i])
	{
		if (!new_txt)
			new_txt = ft_strdup(expander(parse_txt[i], env));
		else
			new_txt = ft_strjoin(new_txt, expander(parse_txt[i], env));
		if (!new_txt)
			exit(-1);
		i++;
	}
	free(command);
	i = 0;
	while (parse_txt[i])
	{
		free(parse_txt[i]);
		i++;
	}
	free(parse_txt);

	return (new_txt);
}

int check_dolar_waar(char *str, int chr)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

void check_dolar(t_list *pipe_lst, t_list *env)
{
	int i;
	t_pipeline *pipeline;

	while (pipe_lst)
	{
		pipeline = pipe_lst->content;
		i = 0;
		while (pipeline->command[i])
		{
			if (check_dolar_waar(pipeline->command[i], '$'))
				pipeline->command[i] = convert_dolar(pipeline->command[i], env);
			else
				i++;
		}
		pipe_lst = pipe_lst->next;
	}
}

void line_(char *line, t_list **env)
{
	t_list *lst;
	t_list *pipe_lst;
	t_pipeline *pipeline;

	lst = tokenize_input(line);
	if (!validate_grammer(lst))
		return;
	pipe_lst = create_parse_list(lst);
	check_dolar(pipe_lst, *env);
	if (pipe_lst)
		pipeline = pipe_lst->content;
	else
		return ;
	if (built_in_and_infile_check(pipeline))
		infile_and_built_in(pipeline, *env);
	else if (check_built_in_file(pipeline))
		built_in(pipeline, env);
	else
		work_execve(pipe_lst, env);
}
