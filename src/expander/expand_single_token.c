/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_single_token.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 16:53:35 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/21 17:29:26 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expand_single_token.h"

static void expand_token(t_token *token, t_list *env_list)
{
	size_t	i;
	char	*expanded_content;
	char	*expansion;
	char	*tmp;
	size_t	len_variable_name;

	i = 0;
	tmp = token->content;
	expanded_content = NULL;
	while (token->content[i] != '\0')
	{
		len_variable_name = 0;
		if (token->content[i] == '$')
		{
			tmp = ft_substr(tmp, 0, i);
			if (expanded_content == NULL)
				expanded_content = tmp;
			else
				expanded_content = ft_strjoin(expanded_content, tmp);
			expansion = expand_single_variable(env_list, token->content[i], &len_variable_name);
			expanded_content = ft_strjoin(expanded_content, expansion);
			i += len_variable_name;
			tmp += i;
			continue ;
		}
		i++;
	}
	token->content = expanded_content;
}

