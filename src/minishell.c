/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
/*   Updated: 2022/01/17 17:11:58 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/signal.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if ('-' == line[0] && '1' == line[1])
			break ;
		free(line);
	}
	free(line);
	return (0);
}
