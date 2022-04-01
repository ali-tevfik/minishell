/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:01:03 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/fork.h"
#include "../../../incl/built_in.h"
#include "../../../incl/minishell.h"
#include "../../parser/parser_data_structs.h"
#include "../../../incl/protect.h"

/*
** Handle the read (<) and here_doc (<<) operator.
** It opens the file for reading, does protect_dup2() and protect_closes again.
*/

static	void	read_infile(t_redirection *redirection)
{
	int	id;

	id = open(redirection->file, O_RDONLY);
	if (id < 0)
	{
		printf("minishell error:");
		exit(1);
	}
	protect_dup2(id, STDIN_FILENO);
	protect_close(id);
}

/*
** Handles the write (>) and append (>>) operator.
** It opens the file for writing, does protect_dup2() and protect_closes again.
*/

static	void	write_outfile(t_redirection *redirection)
{
	int	fd;

	printf("\n\nwrite_outfile\n\n");
	if (redirection->redir_type == WRITE)
		fd = open(redirection->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	
	printf("\n\ntype = %d\n\n", redirection->redir_type);
	if (fd < 0)
	{
		perror("minishell error:");
		exit(1);
	}
	protect_dup2(fd, STDOUT_FILENO);
	protect_close(fd);
}

/*
** Loops over the redirection list for a specific command
** and performs all necessary redirections.
*/

void	handle_redirections(t_pipeline *pipe_line)
{
	t_redirection	*redirection;

	while (pipe_line->redirection)
	{
	printf("\n\nhandle_redirections\n\n");
		redirection = pipe_line->redirection->content;
		if (redirection->redir_type == READ
			|| redirection->redir_type == HERE_DOC)
			read_infile(redirection);
		else
			write_outfile(redirection);
		pipe_line->redirection = pipe_line->redirection->next;
	}
}
