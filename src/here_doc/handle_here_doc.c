/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_here_doc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:39:54 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 17:37:22 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_here_doc.h"

void	del_lst(void *lst)
{
	free(lst);
}

/*
** Write all the element of the list inside a temporary file in /tmp/here_doc
*/

void	write_inputs_to_here_doc(t_list *lst, t_redirection *redirection)
{
	int		id;
	char	new_line;

	new_line = '\n';
	id = open(redirection->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (id < 0)
	{
		printf("minishell: %s: %s\n", "/tmp/here_doc", strerror(errno));
		exit(1);
	}
	while (lst)
	{
		write(id, lst->content, ft_strlen(lst->content));
		write(id, &new_line, sizeof(new_line));
		lst = lst->next;
	}
	protect_close(id);
	ft_lstclear(&lst, del_lst);
}

/*
** Handles the heredocument.
** It takes the user input and adds it to a linked list.
** Finally, it makes a call to write_inputs_to_here_doc
** and puts all the contents inside that file.
*/

static void	handle_here_doc(t_redirection *redirection, char *eof)
{
	t_list	*here_doc_input_list;
	char	*read_txt;

	here_doc_input_list = NULL;
	while (1)
	{
		read_txt = readline("> ");
		if (read_txt == NULL)
			break ;
		else if (strings_are_equal(eof, read_txt))
			break ;
		ft_lstadd_back(&here_doc_input_list, ft_lstnew(read_txt));
	}
	write_inputs_to_here_doc(here_doc_input_list, redirection);
}

void	read_here_doc(t_list *pipe_list)
{
	size_t			i;
	t_redirection	*redirection;
	t_list			*redirection_list;
	char			*eof;
	int exit_status;
	
	i = 0;
	t_list *new_pipe_line = pipe_list;
	int pid = fork();
	if (pid == 0)
	{
		while (pipe_list)
		{
			redirection_list = ((t_pipeline *)(pipe_list->content))->redirection;
			while (redirection_list)
			{
				redirection = redirection_list->content;
				if (redirection->redir_type == HERE_DOC)
				{
					eof = strdup_protect(redirection->file);
					free(redirection->file);
					redirection->file = join_protect("/tmp/here_doc_", protect_itoa(i)); // protect itoa
					handle_here_doc(redirection, eof);
					i++;
				}
				redirection_list = redirection_list->next;
			}
			pipe_list = pipe_list->next;
		}
		exit (2);
	}
	else
	{
		exit_status = wait_and_get_last_exit_status(pid);
	}

	// Loop over parse list again and set all filenames of here docs.
	while (new_pipe_line != NULL)
	{
		redirection_list = ((t_pipeline *)(new_pipe_line->content))->redirection;
		while (redirection_list)
		{
			redirection = redirection_list->content;
			if (redirection->redir_type == HERE_DOC)
			{
				free(redirection->file);
				redirection->file = join_protect("/tmp/here_doc_", protect_itoa(i)); // protect itoa
				i++;
			}
			redirection_list = redirection_list->next;
		}
		new_pipe_line = new_pipe_line->next;
	}
}