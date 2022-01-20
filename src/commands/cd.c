/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:57:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/20 13:30:36 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	cd_command(char *where)
{
	int	result = 0;

	// printf("[%s]\n",skip_space(where + 2));
	result = chdir(skip_space(where + 2));
	if (result == -1)
		perror("Error: ");
}
