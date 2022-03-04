/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_offline.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 18:53:46 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/04 12:30:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"
#include "incl/protect.h"
#include "src/parser/create_parse_list.h"
#include "src/tokenizer/tokenizer.h"
#include "src/libft/libft.h"

void test_working(char *argv[], t_list **env)
{
	char *txt;
	char *small;
	int i;
	char *space;


	i = 2;
	txt = (char *)malloc(sizeof(txt) * 1);
	space = (char *)malloc(sizeof(space) * 2);
	if (!txt || !space)
		exit (-1);
	txt[0] = '\0';
	space[0] = ' ';
	space[1] = '\0';

	while(argv[i])
	{
		small = strdup_protect(argv[i]);
		txt = join_protect(txt, space);
		txt = join_protect(txt, small);
		free(small);

		i++;
	}
	if (txt){
	tokenize_parse_execute(txt, env);
	free(txt);
	}
	free(space);
	exit(1);
}
