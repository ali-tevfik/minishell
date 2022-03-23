/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 12:42:54 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/fork.h"
#include "../../../incl/built_in.h"
#include "../../../incl/minishell.h"
#include "../../parser/parser_data_structs.h"
#include "../../../incl/protect.h"

// void	del_lst(void *lst)
// {
// 	free(lst);
// }

// /*
// ** Write all the element of the list inside a temporary file in /tmp/here_doc
// */

// static	void	write_inputs_to_here_doc(t_list *lst)
// {
// 	int		id;
// 	char	new_line;

// 	new_line = '\n';
// 	id = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (id < 0)
// 	{
// 		printf("minishell: %s: %s\n", "/tmp/here_doc", strerror(errno));
// 		exit(1);
// 	}
// 	while (lst)
// 	{
// 		write(id, lst->content, ft_strlen(lst->content));
// 		write(id, &new_line, sizeof(new_line));
// 		lst = lst->next;
// 	}
// 	close(id);
// 	ft_lstclear(&lst, del_lst);
// }

// /*
// ** Handles the heredocument.
// ** It takes the user input and adds it to a linked list.
// ** Finally, it makes a call to write_inputs_to_here_doc
// ** and puts all the contents inside that file.
// */

// static	void	handle_here_doc(t_redirection *redirection)
// {
// 	t_list	*here_doc_input_list;
// 	char	*read_txt;

// 	here_doc_input_list = NULL;
// 	while (1)
// 	{
// 		read_txt = readline("> ");
// 		if (read_txt == NULL)
// 			break ;
// 		else if (strings_are_equal(redirection->file, read_txt))
// 			break ;
// 		ft_lstadd_back(&here_doc_input_list, ft_lstnew(read_txt));
// 	}
// 	write_inputs_to_here_doc(here_doc_input_list);
// }

/*
** Handle the read (<) and here_doc (<<) operator.
** It opens the file for reading, does dup2() and closes again.
*/

static	void	read_infile(t_redirection *redirection)
{
	int	id;

	id = open(redirection->file, O_RDONLY);
	if (id < 0)
	{
		printf("minishell: %s: %s (line %d in file %s)\n",
			redirection->file, strerror(errno), __LINE__, __FILE__);
		exit(1);
	}
	dup2(id, STDIN_FILENO);
	close(id);
}

/*
** Handles the write (>) and append (>>) operator.
** It opens the file for writing, does dup2() and closes again.
*/

static	void	write_outfile(t_redirection *redirection)
{
	int	fd;

	if (redirection->redir_type == WRITE)
		fd = open(redirection->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", redirection->file, strerror(errno));
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
		redirection = pipe_line->redirection->content;
		if (redirection->redir_type == READ
			|| redirection->redir_type == HERE_DOC)
			read_infile(redirection);
		else
			write_outfile(redirection);
		pipe_line->redirection = pipe_line->redirection->next;
	}
}
