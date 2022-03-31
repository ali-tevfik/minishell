/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:02:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/31 12:56:43 by adoner        ########   odam.nl         */
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

void	clear_data(t_list **pipe_lst, t_list **lst)
{
	ft_lstclear(pipe_lst, free_parse_list_element);
	ft_lstclear(lst, free_token);
}

int	tokenize_parse_execute(char *line, t_list **env, int exit_code)
{
	t_list		*lst;
	t_list		*pipe_lst;
	t_pipeline	*pipeline;
	int			exit_status;

	exit_status = 0;
	lst = tokenize_input(line, *env, exit_code);
	if (lst == NULL)
		return (0);
	if (!validate_grammer(lst))
		return (-1);
	remove_quotes_from_all_tokens(lst);
	pipe_lst = create_parse_list(lst);
	if (!read_here_doc(pipe_lst))
		return (-1);
	pipeline = pipe_lst->content;
	if (!pipeline->command[0])
		return (0);
	if (built_in_and_infile_check(pipeline, pipe_lst))
		exit_status = work_execve(pipe_lst, env);
	else if (is_builtin(pipeline))
		exit_status = execute_builtin(pipeline, env);
	else if (pipeline->command[0])
		exit_status = work_execve(pipe_lst, env);
	clear_data(&pipe_lst, &lst);
	return (exit_status);
}
