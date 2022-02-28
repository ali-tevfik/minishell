/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/28 17:20:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/fork.h"
#include "../../../incl/built_in.h"
#include "../../../incl/minishell.h"
#include "../../parser/parser_data_structs.h"
#include "../../../incl/protect.h"

void	del_lst(void *lst)
{
	free(lst);
}

void write_here_doc(t_list *lst)
{
	int id;
	char new_line;

	new_line = '\n';
	id = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 777);
	while(lst)
	{
		write(id, lst->content, ft_strlen(lst->content));
		write(id, &new_line, sizeof(new_line));
		lst = lst->next;
	}
	close(id);
	ft_lstclear(&lst, del_lst);
}
void	here_doc(t_pipeline *pipline)
{
	t_list	*lst;
	char	*read_txt;
	t_redirection	*redirection;

	redirection = pipline->redirection->content;
	lst = NULL;
	read_txt = readline(">");
	while (match_str(redirection->file, read_txt) != 0){
		ft_lstadd_back(&lst, ft_lstnew(read_txt));
		read_txt = readline(">");
	}
	write_here_doc(lst);
}

int	read_infile(t_pipeline *pipe_line)
{
	int				id;
	t_redirection	*redirection;

	redirection = pipe_line->redirection->content;
	id = -1;
	if (redirection->redir_type == READ)
		id = open(redirection->file, O_RDONLY);
	else
	{
		here_doc(pipe_line);
		redirection->redir_type = READ;
		free(redirection->file);
		redirection->file = strdup_protect("here_doc");
		id = read_infile(pipe_line);
		remove("here_doc");
	}

	if (id < 0)
	{
		printf("infile read error!\n");
		exit(1);
	}
	else
	{
		dup2(id, STDIN_FILENO);
		close(id);
	}
	return (id);
}

static int	write_outfile(t_redirection *redirection)
{
	int				id;

	if (redirection->redir_type == WRITE)
		id = open(redirection->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		id = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (id < 0)
	{
		printf("outfile write error!\n");
		exit(1);
	}
	else
	{
		dup2(id, STDOUT_FILENO);
		close(id);
	}
	return (id);
}

int	fork_file(t_pipeline *pipe_line)
{
	t_redirection	*redirection;
	int				id;

	while (pipe_line->redirection)
	{
		redirection = pipe_line->redirection->content;
		if (redirection->redir_type == READ
			|| redirection->redir_type == HERE_DOC)
			id = read_infile(pipe_line);
		else
			id = write_outfile(redirection);
		pipe_line->redirection = pipe_line->redirection->next;
	}
	return (id);
}
