/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile_and_built_in.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 13:23:11 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 15:30:11 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/fork.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void	infile_and_built_in(t_pipeline *pipeline, t_list *env)
{
	printf("check infile!\n");
	int	id;

	id = fork();
	if (id == 0)
	{
		fork_file(pipeline);
		built_in(pipeline, &env);
	}
	wait_and_get_last_exit_status(id);
}
