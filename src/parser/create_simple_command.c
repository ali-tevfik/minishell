/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_simple_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:10:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/21 12:20:30 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "create_simple_command.h"

/*
** Get the command. Helper function for
** create_simple_command_up_until_pipe_token.
*/

static void	get_command(char **command, t_list **element, size_t i,
						size_t *location)
{
	command[i] = ((t_token *)((*element)->content))->content;
	*element = (*element)->next;
	*location += 1;
}

/*
** Handles the redirection operator in a command.
** A command is everything up until pipe.
*/

static void	handle_redirection_tokens(t_list **redirection_list, \
										t_list **element, size_t *location)
{
	t_token			*current_tkn;
	t_list			*redir_element;
	t_redirection	*redirection;

	current_tkn = (t_token *)((*element)->content);
	redirection = calloc_protect(1, sizeof(*redirection));
	redirection->redir_type = current_tkn->type;
	*element = (*element)->next;
	redirection->file = ((t_token *)((*element)->content))->content;
	redir_element = lstnew_protect(redirection);
	ft_lstadd_back(redirection_list, redir_element);
	*location += 2;
	*element = (*element)->next;
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
	element = token_list;
	i = 0;
	while (element != NULL && ((t_token *)(element->content))->type != PIPE)
	{
		if (is_redirection_token(element->content))
		{
			handle_redirection_tokens(&pipeline->redirection, \
										&element, location);
			continue ;
		}
		get_command(pipeline->command, &element, i, location);
		i++;
	}
	pipeline->command[i] = NULL;
	if (element != NULL && ((t_token *)(element->content))->type == PIPE)
		*location += 1;
	return (pipeline);
}
