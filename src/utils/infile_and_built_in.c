/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile_and_built_in.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 13:23:11 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/16 15:13:16 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/fork.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void	infile_and_built_in(t_pipeline *pipeline, t_list *env)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		fork_file(pipeline);
		wait_and_get_last_exit_status(id);
		built_in(pipeline, &env);
		exit(1);
	}
	if (match_str(pipeline->command[0], "unset") == 0
		|| match_str(pipeline->command[0], "cd") == 0
		|| (match_str(pipeline->command[0], "export") == 0
			&& pipeline->command[1]))
		built_in(pipeline, &env);
}
