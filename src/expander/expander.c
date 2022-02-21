/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 20:55:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/21 16:54:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander(t_list *token_list, t_list *env_list)
{
	char	*word;
	t_token	*token;

	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == WORD)
		{
			// expand if needed.

		}
		token_list = token_list->next;
	}
}