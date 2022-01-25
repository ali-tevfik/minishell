/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/25 12:25:41 by hyilmaz       ########   odam.nl         */
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
	while (token_list != NULL && ((t_token *)(token_list->content))->type != PIPE)
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

t_command	*create_simple_command_up_until_pipe_token(t_list *token_list, \
														size_t *location)
{
	t_command	*command;
	t_list		*element;
	size_t		number_of_command_tokens;
	size_t		i;

	number_of_command_tokens = number_command_tokens(token_list);
	command = ft_calloc(3, sizeof(*command));
	command->command = ft_calloc(number_of_command_tokens + 1, sizeof(char *));
	command->filename = NULL;
	command->redirection_operator = NONE;
	element = token_list;
	i = 0;
	while (element != NULL && ((t_token *)(element->content))->type != PIPE)
	{
		if (((t_token *)(element->content))->type == REDIRECTION)
		{
			if (*(((t_token *)(element->content))->content) == '>' && \
				((t_token *)(element->content))->len_content == 1)
				command->redirection_operator = OUT;
			else if (*(((t_token *)(element->content))->content) == '>' && \
				((t_token *)(element->content))->len_content == 2)
				command->redirection_operator = APPEND;
			else if (*(((t_token *)(element->content))->content) == '<' && \
				((t_token *)(element->content))->len_content == 1)
				command->redirection_operator = READ;
			else
				command->redirection_operator = HERE_DOC;
			element = element->next;
			/* Now at filename */
			command->filename = ft_substr(((t_token *)(element->content))->content, 0, \
										((t_token *)(element->content))->len_content);
			*location += 2;
			element = element->next;
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
