/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevfik <tevfik@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/11 13:09:29 by tevfik        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/01/31 15:27:19 by adoner        ########   odam.nl         */
=======
/*   Updated: 2022/01/25 15:29:02 by hyilmaz       ########   odam.nl         */
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	env = add_envp(envp);
	argc = 1;
	argv = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, "", 1) != 0)
			add_history(line);
		if ('-' == line[0] && '1' == line[1])
			break ;
		line_(line, &env);
		free(line);
	}
	free(line);
	return (0);
}
