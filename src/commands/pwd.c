/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:39:09 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/03 15:19:22 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	pwd_command(void)
{
	char	*path;

	path = (char *) malloc(sizeof(path) * PATH_MAX_LEN);
	if (!path)
		printf("malloc error");
	printf("%s\n", getcwd(path, PATH_MAX_LEN));
	free(path);
}
