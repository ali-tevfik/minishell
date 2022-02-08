/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   waiting_last_child.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:45:43 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 11:53:26 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/commands.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"

int	wait_and_get_last_exit_status(int last_process_pid)
{
	int	pid;
	int	last_process_status;
	int	status;

	pid = 1;
	last_process_status = 0;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_process_pid)
		{
			if (WIFEXITED(status))
				last_process_status = WEXITSTATUS(status);
		}
	}
	return (last_process_status);
}
