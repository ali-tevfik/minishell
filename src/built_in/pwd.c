/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:39:09 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/21 14:41:49 by adoner        ########   odam.nl         */
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

void	pwd_command(t_pipeline *pipeline)
{
	char	*ret;

	if (pipeline->command[1])
		printf("bad option %s\n", pipeline->command[1]);
	else
	{
		ret = getcwd(NULL, 0);
		if (ret == NULL)
		{
			perror("Error");
			if (errno == ENOMEM)
				exit (1);
			return ;
		}
		printf("%s\n", ret);
		free(ret);
	}
}
