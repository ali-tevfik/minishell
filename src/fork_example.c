/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_example.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/01 13:33:05 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "parser/create_parse_list.h"
#include "../incl/minishell.h"
#include "../incl/commands.h"

// void childeren_func(t_command command_lst)
// {
// }

// void parent_func(t_command command_lst)
// {}

void fork_func(t_list *command_lst)
{
	int	fd[2];
	int	id;

	if (pipe(fd) < 0)
		perror("Error with pipe");
	id = fork();
	if (id < 0)
		perror("Error with fork");
	printf("yazi %d \n",ft_lstsize(command_lst));
	// if (id == 0)
	// 	childeren_func(command_lst);
	// else
	// 	parent_func(command_lst);
}
