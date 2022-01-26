/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 14:00:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/*
** Returns the amount of command tokens in a command.
** The commands tokens are all tokens except for the redirection operator
** and filename for redirection.
*/

static size_t	number_command_tokens(t_list *token_list)
{
	size_t	i;

	i = 0;
	while (token_list != NULL && \
			((t_token *)(token_list->content))->type != PIPE)
	{
		if (((t_token *)(token_list->content))->type == REDIRECTION)
		{
			token_list = token_list->next;
			token_list = token_list->next;
			continue ;
		}
		token_list = token_list->next;
		i++;
	}
	return (i);
}

/*
** Allocates memory for command struct and initializes variables.
*/

t_command	*init_command(t_list *token_list)
{
	size_t		number_of_command_tokens;
	t_command	*command;

	number_of_command_tokens = number_command_tokens(token_list);
	command = ft_calloc(3, sizeof(*command));
	command->command = ft_calloc(number_of_command_tokens + 1, sizeof(char *));
	command->in_file = NULL;
	command->out_file = NULL;
	command->redirection_operator_in = NONE;
	command->redirection_operator_out = NONE;
	return (command);
}

/* 
** Handles the redirection operator in a command.
** A command is everything up until pipe.
*/

static int	handle_redirection_tokens(t_command *command, t_list **element, \
										size_t *location)
{
	t_token	*current_token;
	
	current_token = (t_token *)((*element)->content);
	if (*(current_token->content) == '>' && current_token->len_content == 1)
		command->redirection_operator_out = OUT;
	else if (*(current_token->content) == '>' && current_token->len_content == 2)
		command->redirection_operator_out = APPEND;
	else if (*(current_token->content) == '<' && current_token->len_content == 1)
		command->redirection_operator_in = READ;
	else
		command->redirection_operator_in = HERE_DOC;
	*element = (*element)->next;
	if (*(current_token->content) == '<')
		command->in_file = ft_substr(((t_token *)((*element)->content))->content, \
								0, ((t_token *)((*element)->content))->len_content);
	else if (*(current_token->content) == '>')
		command->out_file = ft_substr(((t_token *)((*element)->content))->content, \
								0, ((t_token *)((*element)->content))->len_content);
	*location += 2;
	*element = (*element)->next;
	return (1);
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
	element = token_list;
	i = 0;
	while (element != NULL && ((t_token *)(element->content))->type != PIPE)
	{
		if (((t_token *)(element->content))->type == REDIRECTION)
		{
			handle_redirection_tokens(command, &element, location);
			continue ;
		}
		command->command[i] = ft_substr(
				((t_token *)(element->content))->content, 0, \
				((t_token *)(element->content))->len_content);
		element = element->next;
		*location += 1;
		i++;
	}
	command->command[i] = NULL;
	if (element != NULL && ((t_token *)(element->content))->type == PIPE)
		*location += 1;
	return (command);
}
