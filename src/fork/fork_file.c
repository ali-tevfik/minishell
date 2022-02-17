/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/17 13:48:31 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/fork.h"
#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void del_lst(void *lst)
{
	free(lst);
}
void here_doc(t_pipeline *pipline)
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
	while(lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	ft_lstclear(&lst, del_lst);
}

int	read_infile(t_pipeline *pipe_line)
{
	int				id;
	t_redirection	*redirection;

	redirection = pipe_line->redirection->content;
	id = 0;
	if (redirection->redir_type == READ)
		id = open(redirection->file, O_RDONLY);
	else
	{
		here_doc(pipe_line);
		exit(1);
	}

	if (id < 0)
	{
		printf("infile read error!\n");
		exit(1);
	}
	else
	{
		dup2(id, 0);
		close(id);
	}
	return (id);
}

int	write_outfile(t_pipeline *pipe_line)
{
	int				id;
	t_redirection	*redirection;

	redirection = pipe_line->redirection->content;
	if (redirection->redir_type == OUT)
		id = open(redirection->file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		id = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (id < 0)
	{
		printf("outfile write error!\n");
		exit(1);
	}
	else
	{
		dup2(id, 1);
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
			id = write_outfile(pipe_line);
		pipe_line->redirection = pipe_line->redirection->next;
	}
	return (id);
}
