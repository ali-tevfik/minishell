/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_simple_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:10:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 18:20:00 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "create_simple_command.h"

/*
** Get the filenames belonging to the redirection.
*/

static bool	get_filenames(t_command *command, t_list **element,
							t_token *current_tkn)
{
	if (*(current_tkn->content) == '<')
	{
		command->in_file = ft_substr(
				((t_token *)((*element)->content))->content, \
				0, ((t_token *)((*element)->content))->len_content);
		if (command->in_file == NULL)
		{
			perror("Error with malloc");
			return (false);
		}
	}
	else if (*(current_tkn->content) == '>')
	{
		command->out_file = ft_substr(
				((t_token *)((*element)->content))->content, \
				0, ((t_token *)((*element)->content))->len_content);
		if (command->out_file == NULL)
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

static bool	get_command(t_command *command, t_list **element, size_t i,
						size_t *location)
{
	command->command[i] = ft_substr(
			((t_token *)((*element)->content))->content, 0, \
			((t_token *)((*element)->content))->len_content);
	if (command->command[i] == NULL)
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

static bool	handle_redirection_tokens(t_command *command, t_list **element, \
										size_t *location)
{
	t_token	*current_tkn;

	current_tkn = (t_token *)((*element)->content);
	if (*(current_tkn->content) == '>' && current_tkn->len_content == 1)
		command->redirection_operator_out = OUT;
	else if (*(current_tkn->content) == '>' && current_tkn->len_content == 2)
		command->redirection_operator_out = APPEND;
	else if (*(current_tkn->content) == '<' && current_tkn->len_content == 1)
		command->redirection_operator_in = READ;
	else
		command->redirection_operator_in = HERE_DOC;
	*element = (*element)->next;
	if (!get_filenames(command, element, current_tkn))
		return (false);
	*location += 2;
	*element = (*element)->next;
	return (true);
}

/*
** Creates a t_command struct with one command,
** up until the first token is encounterd.
** Location is an index of which is the current token (so starts form zero).
** command_tokens are the tokens that are used for the command,
** for example ls -l, so it excludes the redirection operator and filename.
*/

t_command	*create_simple_command_up_until_pipe_token(t_list *token_list, \
														size_t *location)
{
	t_command	*command;
	t_list		*element;
	size_t		i;

	command = init_command(token_list);
	if (command == NULL)
		return (NULL);
	element = token_list;
	i = 0;
	while (element != NULL && ((t_token *)(element->content))->type != PIPE)
	{
		if (((t_token *)(element->content))->type == REDIRECTION)
		{
			if (!handle_redirection_tokens(command, &element, location))
				return (NULL);
			continue ;
		}
		if (!get_command(command, &element, i, location))
			return (false);
		i++;
	}
	command->command[i] = NULL;
	if (element != NULL && ((t_token *)(element->content))->type == PIPE)
		*location += 1;
	return (command);
}
