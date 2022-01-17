/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/01/17 15:46:57 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if ('-' == line[0] && '1' == line[1])
			break ;
		tokenize_input(line);
		free(line);
	}
	free(line);
	return (0);
}
