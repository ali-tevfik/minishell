/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_simple_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:10:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/07 14:53:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "create_simple_command.h"

/*
** Get the filenames belonging to the redirection.
*/

static bool	get_filenames(t_redirection *redirection, t_list **element,
							t_token *current_tkn)
{
	if (*(current_tkn->content) == '<')
	{
		redirection->file = ft_substr(
				((t_token *)((*element)->content))->content, \
				0, ((t_token *)((*element)->content))->len_content);
		if (redirection->file == NULL)
		{
			perror("Error with malloc");
			return (false);
		}
	}
	else if (*(current_tkn->content) == '>')
	{
		redirection->file = ft_substr(
				((t_token *)((*element)->content))->content, \
				0, ((t_token *)((*element)->content))->len_content);
		if (redirection->file == NULL)
		{
			perror("Error with malloc");
			return (false);
		}
	}
	return (true);
}

/*
** Get the command. Helper function for 
** create_simple_command_up_until_pipe_token.
*/

static bool	get_command(char **command, t_list **element, size_t i,
						size_t *location)
{
	command[i] = ft_substr(
			((t_token *)((*element)->content))->content, 0, \
			((t_token *)((*element)->content))->len_content);
	if (command[i] == NULL)
	{
		perror("Error with malloc:");
		return (false);
	}
	*element = (*element)->next;
	*location += 1;
	return (true);
}

/* 
** Handles the redirection operator in a command.
** A command is everything up until pipe.
*/

static bool	handle_redirection_tokens(t_list **redirection_list, \
										t_list **element, size_t *location)
{
	t_token			*current_tkn;
	t_list			*redir_element;
	t_redirection	*redirection;

	current_tkn = (t_token *)((*element)->content);
	redirection = ft_calloc(1, sizeof(*redirection));
	if (redirection == NULL)
		return (false);
	if (*(current_tkn->content) == '>' && current_tkn->len_content == 1)
		redirection->redir_type = OUT;
	else if (*(current_tkn->content) == '>' && current_tkn->len_content == 2)
		redirection->redir_type = APPEND;
	else if (*(current_tkn->content) == '<' && current_tkn->len_content == 1)
		redirection->redir_type = READ;
	else
		redirection->redir_type = HERE_DOC;
	*element = (*element)->next;
	if (!get_filenames(redirection, element, current_tkn))
		return (false);
	redir_element = ft_lstnew(redirection);
	if (redir_element == NULL)
		return (false);
	ft_lstadd_back(redirection_list, redir_element);
	*location += 2;
	*element = (*element)->next;
	return (true);
}

/*
** Creates a t_pipeline struct with one simple pipeline,
** up until the first token is encounterd.
** Location is an index of which is the current token (so starts form zero).
** command_tokens are the tokens that are used for the command,
** for example ls -l, so it excludes the redirection operator and filename.
*/

t_pipeline	*create_simple_pipeline_up_until_pipe_token(t_list *token_list, \
														size_t *location)
{
	t_pipeline	*pipeline;
	t_list		*element;
	size_t		i;

	pipeline = init_pipeline(token_list);
	if (pipeline == NULL)
		return (NULL);
	element = token_list;
	i = 0;
	while (element != NULL && ((t_token *)(element->content))->type != PIPE)
	{
		if (((t_token *)(element->content))->type == REDIRECTION)
		{
			if (!handle_redirection_tokens(&pipeline->redirection, \
											&element, location))
				return (NULL);
			continue ;
		}
		if (!get_command(pipeline->command, &element, i, location))
			return (false);
		i++;
	}
	pipeline->command[i] = NULL;
	if (element != NULL && ((t_token *)(element->content))->type == PIPE)
		*location += 1;
	return (pipeline);
}
