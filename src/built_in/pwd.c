/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:39:09 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 15:19:42 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include <limits.h>
#include "../parser/parser_data_structs.h"
/*
** Use PATH_MAX from limists.h
** check retturn value of getcwd
** Make path = NULL, getcwd handles the allocating itself
*/

int	pwd_command(t_pipeline *pipeline)
{
	char	*ret;
	int		exit_code;

	exit_code = 0;
	if (pipeline->command[1][0] == '-')
	{
		printf("bad option %s\n", pipeline->command[1]);
		exit_code = 1;
	}
	else
	{
		ret = getcwd(NULL, 0);
		if (ret == NULL)
		{
			perror("Error");
			if (errno == ENOMEM)
				exit (1);
			return (-1);
		}
		printf("%s\n", ret);
		free(ret);
	}
	return (exit_code);
}
