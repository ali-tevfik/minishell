/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_here_doc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:39:54 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/30 14:39:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_here_doc.h"

/*
** Write all the element of the list inside a temporary file in /tmp/here_doc
*/

static void	write_inputs_to_here_doc(t_list *lst, t_redirection *redirection)
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
	close(id);
	ft_lstclear(&lst, free);
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
	free(eof);
	write_inputs_to_here_doc(here_doc_input_list, redirection);
}

/*
** After the here document temporary files are created,
** this function updates the parse_list.
*/

static void	set_here_doc_files(t_list *pipe_list)
{
	size_t			i;
	t_redirection	*redirection;
	t_list			*redirection_list;

	i = 0;
	while (pipe_list != NULL)
	{
		redirection_list = ((t_pipeline *)(pipe_list->content))->redirection;
		while (redirection_list)
		{
			redirection = redirection_list->content;
			if (redirection->redir_type == HERE_DOC)
			{
				free(redirection->file);
				redirection->file = join_protect("/tmp/here_doc_",
						protect_itoa(i));
				i++;
			}
			redirection_list = redirection_list->next;
		}
		pipe_list = pipe_list->next;
	}
}

/*
** If there are here documents present
** create the temporary files inside of /tmp directory.
*/

static void	child_here_doc(t_list *pipe_list)
{
	t_here_doc_params	params;
	t_list				*redirection_list;
	t_redirection		*redirection;

	signal(SIGINT, SIG_DFL);
	params.i = 0;
	while (pipe_list)
	{
		redirection_list = ((t_pipeline *)(pipe_list->content))->redirection;
		while (redirection_list)
		{
			redirection = redirection_list->content;
			if (redirection->redir_type == HERE_DOC)
			{
				params.eof = strdup_protect(redirection->file);
				redirection->file = join_protect("/tmp/here_doc_",
						protect_itoa(params.i));
				handle_here_doc(redirection, params.eof);
				params.i += 1;
			}
			redirection_list = redirection_list->next;
		}
		pipe_list = pipe_list->next;
	}
	exit (0);
}

/*
** Creates a process and loopes over all commands in the pipeline.
** For each here document found,
** it creates a file in the format /tmp/here_doc_{0,1,...,n}.
** After the process is finished, 
** loop again over the pipe_line list and change all here document
** files to /tmp/here_doc_{0,1,...,n}.
*/

bool	read_here_doc(t_list *pipe_list)
{
	int	pid;
	int	exit_status;

	g_interactive = 2;
	pid = fork();
	if (pid == -1)
		exit (-1);
	if (pid == 0)
		child_here_doc(pipe_list);
	exit_status = wait_and_get_last_exit_status(pid);
	g_interactive = 1;
	if (exit_status == 128 + SIGINT)
		return (false);
	set_here_doc_files(pipe_list);
	return (true);
}
