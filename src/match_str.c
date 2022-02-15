/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   match_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 18:16:53 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 15:22:06 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "parser/parser_data_structs.h"
#include "parser/create_simple_command.h"
#include "tokenizer/tokenizer.h"
#include "../incl/fork.h"
#include "parser/create_parse_list.h"

int	match_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
	{
		if (!s2[i])
			return (0);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i])
		return (0);
	return (1);
}
