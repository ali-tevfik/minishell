/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_offline.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 18:53:46 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/17 19:18:40 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

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
	txt[0] = '\0';
	space[0] = ' ';
	space[1] = '\0';

	while(argv[i])
	{
		small = ft_strdup(argv[i]);
		txt = ft_strjoin(txt, space);
		txt = ft_strjoin(txt, small);
		free(small);

		i++;
	}

	printf("hello  %s\n", txt);
	if (txt){
	line_(txt, env);
	free(txt);
	}
	free(space);
	exit(1);
}
