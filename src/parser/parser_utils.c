/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:53:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/25 16:40:58 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/*
** Print the parse list commands.
*/

void	print_commands(t_list *parse_list)
{
	size_t		i;
	t_pipeline	*pipeline;

	while (parse_list)
	{
		pipeline = parse_list->content;
		i = 0;
		while (pipeline->command[i] != NULL)
		{
			printf("%s ", pipeline->command[i]);
			i++;
		}
		printf("\n");
		parse_list = parse_list->next;
	}
}

/*
** Free redirection list element.
** The type of the element is (t_redirection *).
*/

static void	free_redirection_element(void *redirection)
{
	free(((t_redirection *)redirection)->file);
}

/*
** Free an element of the parse_list.
** The type of the element is (t_pipeline *).
*/

void	free_parse_list_element(void *pipeline)
{
	size_t		i;

	i = 0;
	while (((t_pipeline *)(pipeline))->command[i] != NULL)
	{
		free(((t_pipeline *)(pipeline))->command[i]);
		i++;
	}
	free(((t_pipeline *)(pipeline))->command);
	ft_lstclear(&((t_pipeline *)(pipeline))->redirection, free_redirection_element);
}
/*
** Returns the amount of command tokens in a command.
** The tokens are command-tokens except for the redirection operator
** and filename for redirection.
*/

static size_t	number_command_tokens(t_list *token_list)
{
	size_t	i;

	i = 0;
	while (token_list != NULL && \
			((t_token *)(token_list->content))->type != PIPE)
	{
		if (is_redirection_token(token_list->content))
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

t_pipeline	*init_pipeline(t_list *token_list)
{
	size_t		number_of_command_tokens;
	t_pipeline	*pipeline;

	number_of_command_tokens = number_command_tokens(token_list);
	pipeline = calloc_protect(1, sizeof(*pipeline));
	pipeline->command = calloc_protect(number_of_command_tokens + 1, \
									sizeof(*pipeline->command));
	pipeline->redirection = NULL;
	return (pipeline);
}
