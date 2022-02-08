/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:00:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 12:48:09 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/commands.h"
#include "../executor/find_command.h"
#include "../../incl/fork.h"
#include "../parser/parser_data_structs.h"



void first_child(t_command *command, t_list *env, char **envp, int fd[2])
{
	int id;

	id = fork();
	if (id == 0)
	{
		find_command(command, env);
		// if (command->in_file != NONE)
		// {
		// 	// fd[0] = read_infile(command);
		// 	dup2(fd[0], 0);
		// }
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execve(command->command[0], command->command, envp);
		perror("Error with execve");
	}
}

void middle_child(t_command *command, t_list *env, char **envp, int fd[2], int endfile)
{
	int id;

	id = fork();
	if (id == 0)
	{
		dup2(fd[1],1);
		dup2(endfile,0);
		close(fd[0]);
		close(fd[1]);
		close(endfile);
		find_command(command, env);
		execve(command->command[0], command->command, envp);
		perror("Error with execve");
	}

}

void last_child(t_command *command, t_list *env, char **envp, int fd[2], int *lastid)
{
	*lastid = fork();
	if (*lastid == 0)
	{
		find_command(command, env);
		// if (command->redirection_operator_out != NONE)
		// {
		// 	fd[1] = write_outfile(command);
		// 	dup2[fd[1],1];
		// }
		close(fd[1]);
		dup2(fd[0],0);
		close(fd[0]);
		execve(command->command[0], command->command, envp);
		perror("Error with execve");
	}
}

void fork_func(t_list *command_lst, char *envp[], t_list *env, int *last_id)
{
	int	fd[2];
	int	end_file;
	int	i;
	t_command	*command;

	i = 0;
	end_file = -1;
	while (command_lst)
	{
		command = command_lst->content;
		if (command_lst->next)
		{
			if (pipe(fd) == -1)
				exit(0);
		}
		if (i == 0)
			first_child(command, env, envp, fd);
		else if (!command_lst->next)
			last_child(command, env, envp, fd, last_id);
		else
			middle_child(command, env, envp, fd, end_file);
		end_file = fd[0];
		command_lst = command_lst->next;
		if (command_lst)
			close(fd[1]);
		i++;
	}
}
