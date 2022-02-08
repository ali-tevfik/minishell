/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:39:09 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 17:35:11 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"
#include <limits.h>

/*
** Use PATH_MAX from limists.h
** check retturn value of getcwd
** Make path = NULL, getcwd handles the allocating itself
*/

void	pwd_command(void)
{
	char	*path;
	char	*ret;

	path = NULL;
	ret = getcwd(path, 0);
	if (ret == NULL)
	{
		perror("Error");
		if (errno == ENOMEM)
			exit (1);
		return ;
	}
	printf("%s\n", ret);
	free(path);
}
