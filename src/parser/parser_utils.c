/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 17:43:30 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/*
** Allocates memory for command struct and initializes variables.
*/

t_command	*init_command(t_list *token_list)
{
	size_t		number_of_command_tokens;
	t_command	*command;

	number_of_command_tokens = number_command_tokens(token_list);
	command = ft_calloc(3, sizeof(*command));
	if (command == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	command->command = ft_calloc(number_of_command_tokens + 1, sizeof(char *));
	if (command->command == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	command->in_file = NULL;
	command->out_file = NULL;
	command->redirection_operator_in = NONE;
	command->redirection_operator_out = NONE;
	return (command);
}

/*
** Returns the amount of command tokens in a command.
** The commands tokens are all tokens except for the redirection operator
** and filename for redirection.
*/

size_t	number_command_tokens(t_list *token_list)
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
