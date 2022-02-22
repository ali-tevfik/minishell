/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_expander.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 01:31:14 by tevfik        #+#    #+#                 */
/*   Updated: 2022/02/22 17:18:30 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
char *check_expander(char *line, t_list *env);


int check_dolar_waar(char *str, int chr)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}

int check_quotes(char *line, char ch)
{
	int i;
	int total;

	total = 0;
	i = 0;
	while(line[i])
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

int finished_expander(char *txt)
{
	int i;

	i = 0;
	while (txt[i])
	{
		if (!(ft_isalnum(txt[i]) || txt[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

char *crete_first_deel(char *line)
{
	char *first_deel;
	int end_index;

	end_index = check_dolar_waar(line, '$');
	first_deel = ft_substr(line, 0, end_index);
	if (!first_deel)
		exit(-1);
	// printf("first deel %s \n", first_deel);
	return (first_deel);
}

char *create_expander_deel(char *line, t_list *env)
{
	int start_expander_index;
	int end_expander_index;
	char *txt;
	char *return_expander;

	start_expander_index = check_dolar_waar(line, '$');
	end_expander_index = finished_expander((line + start_expander_index + 1));
	txt = ft_substr(line, start_expander_index + 1, end_expander_index);
	// printf("create_expander_deel  %s index %d\n", txt, end_expander_index);
	return_expander = expander(txt, env);
	if (txt)
		free(txt);

	// printf("create_expander_deel find expander %s \n", return_expander);
	return (return_expander);
}

char *create_end_deel(char *line)
{
	char *end;
	int end_index;
	int start_index;

	start_index = check_dolar_waar(line, '$');
	end_index = finished_expander((line + start_index + 1));
	end = ft_substr(line, end_index + start_index + 1, ft_strlen(line));
	if (!end)
		exit(-1);
	return (end);
}
char *convert_expander(char *line, t_list *env)
{
	char *first_deel;
	char *expander_deel;
	char *end_deel;
	char *all_txt;

	first_deel = crete_first_deel(line);
	expander_deel = create_expander_deel(line, env);
	end_deel = create_end_deel(line);
	if (!expander_deel)
		expander_deel = ft_strdup("");
	if (first_deel)
		all_txt = ft_strjoin(first_deel, expander_deel);
	else
		all_txt = ft_strdup(expander_deel);
	if (end_deel)
		all_txt = ft_strjoin(all_txt, end_deel);
	if (first_deel)
		free(first_deel);
	if (end_deel)
		free(end_deel);

	return (all_txt);
}

char *check_expander(char *line, t_list *env)
{
	while (check_dolar_waar(line, '$') != -1)
	{
		if (check_quotes(line,'\'') == 0)
			line = convert_expander(line, env);
		else
			break ;
	}
	return (line);
}
