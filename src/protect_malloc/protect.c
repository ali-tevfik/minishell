/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 16:46:25 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/18 12:22:01 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/protect.h"
#include <stdlib.h>

char	**split_protect(char *txt, char ch)
{
	char	**data;

	data = ft_split(txt, ch);
	if (!data)
		exit(-1);
	return (data);
}

char	*join_protect(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	if (!s3)
		exit (-1);
	return (s3);
}

char	*strdup_protect(char *s1)
{
	char	*s2;

	s2 = ft_strdup(s1);
	if (!s2)
		exit (-1);
	return (s2);
}

char	*substr_protect(char *s1, int start, int finish)
{
	char	*s2;

	s2 = ft_substr(s1, start, finish);
	if (!s2)
		exit(-1);
	return (s2);
}

void	*calloc_protect(size_t count, size_t size)
{
	void	*s1;

	s1 = ft_calloc(count, size);
	if (!s1)
		exit(-1);
	return (s1);
}

t_list	*lstnew_protect(void *content)
{
	t_list	*list;

	list = ft_lstnew(content);
	if (!list)
		exit (-1);
	return (list);
}
