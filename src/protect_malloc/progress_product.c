/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   progress_product.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:42:38 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 18:53:59 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	protect_dup2(int fd, int i)
{
	int	result;

	result = dup2(fd, i);
	if (result == -1)
	{
		perror("dup2 error:");
		exit(1);
	}
}

void	protect_close(int id)
{
	int	result;

	result = close(id);
	if (result == -1)
		exit(1);
}
