/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 01:31:14 by tevfik        #+#    #+#                 */
/*   Updated: 2022/03/31 16:34:23 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../../incl/expander.h"
#include "../../incl/protect.h"
#include "../parser/parser_data_structs.h"

char	*crete_first_deel(char *line)
{
	char	*first_deel;
	int		end_index;

	end_index = check_dolar_waar(line, '$');
	first_deel = substr_protect(line, 0, end_index);
	return (first_deel);
}

char	*skip_space(char *line)
{
	int		x;
	int		i;
	char	*new_txt;

	x = 0;
	new_txt = (char *)malloc(sizeof(char *) * find_how_many_chr(line));
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			new_txt[x] = line[i];
			x++;
		}
		i++;
	}
	new_txt[i] = '\0';
	return (new_txt);
}

int	find_how_many_chr(char *line)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			x++;
		i++;
	}
	x++;
	return (x);
}

bool	check_exit_code(char *line)
{
	char	*test;

	test = skip_space(line);
	if (strings_are_equal(test, "$?"))
	{
		free(test);
		return (true);
	}
	free(test);
	return (false);
}
