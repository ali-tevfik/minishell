/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_dolar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 01:31:14 by tevfik        #+#    #+#                 */
/*   Updated: 2022/02/21 18:13:19 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../parser/create_parse_list.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

char *convert_dolar(char *command, t_list *env)
{
	char **parse_txt;
	int i;
	char *new_txt;
	i = 0;
	parse_txt = ft_split(command, '$');
	printf("parse[0] %s parse[1] %s\n",parse_txt[0],parse_txt[1]);
	new_txt = NULL;
	while (parse_txt[i])
	{
		if (expander(parse_txt[i], env))
		{
			printf("insede expender[%s]!\n",parse_txt[i]);
			if (!new_txt)
				new_txt = ft_strdup(expander(parse_txt[i], env));
			else
				new_txt = ft_strjoin(new_txt, expander(parse_txt[i], env));
			if (!new_txt)
				exit(-1);
		}
		else
			new_txt = ft_strdup(parse_txt[i]);
		i++;
	}
	free(command);
	i = 0;
	while (parse_txt[i])
	{
		free(parse_txt[i]);
		i++;
	}
	if (parse_txt)
		free(parse_txt);
	printf("return value convert = %s\n", new_txt);
	return (new_txt);
}

int check_dolar_waar(char *str, int chr)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

void check_dolar(t_list *pipe_lst, t_list *env)
{
	int i;
	t_pipeline *pipeline;

	while (pipe_lst)
	{
		pipeline = pipe_lst->content;
		i = 0;
		while (pipeline->command[i])
		{
			if (check_dolar_waar(pipeline->command[i], '$'))
				pipeline->command[i] = convert_dolar(pipeline->command[i], env);
			else
				i++;
		}
		pipe_lst = pipe_lst->next;
	}
}
