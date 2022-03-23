/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 16:46:25 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 17:41:30 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/protect.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*lstnew_protect(void *content)
{
	t_list	*list;

	list = ft_lstnew(content);
	if (!list)
	{
		perror("Malloc failed");
		exit (-1);
	}
	return (list);
}

char	*protect_itoa(int i)
{
	char	*txt;

	txt = ft_itoa(i);
	if (!txt)
		exit(1);
	return (txt);
}
