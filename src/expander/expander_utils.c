/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 01:31:14 by tevfik        #+#    #+#                 */
/*   Updated: 2022/03/29 12:37:23 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
#include <stdio.h>

int	check_dolar_waar(char *str, int chr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}

int	finished_expander(char *txt)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		if (!(ft_isalnum(txt[i]) || txt[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

int	check_quotes_close(char *line)
{
	bool	open_quotes;
	int		i;
	bool	open_double_quotes;

	i = 0;
	open_quotes = false;
	open_double_quotes = false;
	while (line[i])
	{
		if (!open_quotes && !open_double_quotes && line[i] == '$')
			return (-1);
		if (line[i] == '\"' && !open_quotes)
			open_double_quotes = !open_double_quotes;
		if (line[i] == '\'' && !open_double_quotes)
		{
			open_quotes = !open_quotes;
			if (!open_quotes)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	check_quotes(char *line, char ch)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ch)
			total++;
		i++;
	}
	if (total == 0)
		return (0);
	if (total == 1)
		return (-1);
	else
		return (1);
}

int	check_emtpy_dolar(char *line)
{
	int	start;
	int	end;

	start = check_dolar_waar(line, '$');
	end = finished_expander((line + start + 1));
	if (end == 0)
		return (1);
	else
		return (0);
}
