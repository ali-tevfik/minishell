/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_expander.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 01:31:14 by tevfik        #+#    #+#                 */
/*   Updated: 2022/03/21 14:56:37 by adoner        ########   odam.nl         */
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

char	*create_expander_deel(char *line, t_list *env)
{
	int		start_expander_index;
	int		end_expander_index;
	char	*txt;
	char	*return_expander;

	start_expander_index = check_dolar_waar(line, '$');
	end_expander_index = finished_expander((line + start_expander_index + 1));
	if (end_expander_index == 0)
		return (strdup_protect("$"));
	txt = substr_protect(line, start_expander_index + 1, end_expander_index);
	return_expander = expander(txt, env);
	if (!return_expander)
		return_expander = strdup_protect("");
	if (txt)
		free(txt);
	return (return_expander);
}

char	*create_end_deel(char *line)
{
	char	*end;
	int		end_index;
	int		start_index;

	start_index = check_dolar_waar(line, '$');
	end_index = finished_expander((line + start_index + 1));
	end = substr_protect(line, end_index + start_index + 1, ft_strlen(line));
	return (end);
}

char	*convert_expander(char *line, t_list *env)
{
	char	*first_deel;
	char	*expander_deel;
	char	*end_deel;
	char	*all_txt;

	first_deel = crete_first_deel(line);
	expander_deel = create_expander_deel(line, env);
	end_deel = create_end_deel(line);
	if (!expander_deel)
		expander_deel = strdup_protect("");
	if (first_deel)
		all_txt = join_protect(first_deel, expander_deel);
	else
		all_txt = strdup_protect(expander_deel);
	if (end_deel)
		all_txt = join_protect(all_txt, end_deel);
	if (first_deel)
		free(first_deel);
	if (end_deel)
		free(end_deel);
	return (all_txt);
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

char	*skip_space(char *line)
{
	int	x;
	int	i;
	char	*new_txt;

	x = 0;
	new_txt = (char *)malloc(sizeof(char *) * find_how_many_chr(line));
	i = 0;
	while(line[i])
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

/*
** Frees input line and return expanded_line.
** Expands the variables (if any) in the line argument.
*/

char	*expand_input_string(char *line, t_list *env, int exit_code)
{
	char	*next_dolar;
	int		start;
	int		simple_quotes;

	if (strings_are_equal(skip_space(line), "$?"))
		return (ft_itoa(exit_code));
	while (check_dolar_waar(line, '$') != -1)
	{
		if (check_quotes(line, '\'') == 0)
		{
			line = convert_expander(line, env);
			if (check_emtpy_dolar(line))
			{
				start = check_dolar_waar(line, '$');
				next_dolar = expand_input_string(line + start + 1, env, exit_code);
				return (join_protect(substr_protect(line, 0, start + 1), next_dolar));
			}
		}
		else
		{
			simple_quotes = check_dolar_waar(line, '\'');
			next_dolar = expand_input_string(line + simple_quotes + 1, env, exit_code);
			return (join_protect(substr_protect(line, 0, simple_quotes + 1),
					next_dolar));
		}
	}
	return (strdup_protect(line));
}
