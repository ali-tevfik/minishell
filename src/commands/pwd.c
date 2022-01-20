/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:39:09 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/18 15:58:18 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	pwd_command(void)
{
	char	*path;

	path = (char *) malloc(sizeof(path) * PATH_MAX);
	if (!path)
		printf("malloc error");
	printf("%s\n", getcwd(path, PATH_MAX));
	free(path);
}
