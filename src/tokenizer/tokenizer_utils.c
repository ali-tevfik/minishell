/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:50:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/24 11:02:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

bool	is_char_a_delimiter(char c)
{
	int			i;
	const char	*delimiters = "|<>\'\"\n \t\0";

	i = 0;
	while (i < 9)
	{
		if (delimiters[i] == c)
			return (true);
		i++;
	}
	return (false);
}

t_token	*create_token(char *content, size_t len_content, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->content = content;
	token->len_content = len_content;
	token->type = type;
	return (token);
}

void	free_token(void *token)
{
	free((t_token *)token);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || \
		c == '\v' || c == ' ')
		return (1);
	return (0);
}

void	print_token_list(t_list *token_list)
{
	t_list		*head;
	int			i;

	i = 0;
	head = token_list;
	while (1)
	{
		printf("content     = %s\n", ((t_token *)(head->content))->content);
		printf("len_content = %zu\n", ((t_token *)(head->content))->len_content);
		printf("type        = %d\n", ((t_token *)(head->content))->type);
		printf("\n");
		if (head->next == NULL)
			return ;
		head = head->next;
		i++;
	}
}
