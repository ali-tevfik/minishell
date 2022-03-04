/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   match_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 18:16:53 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/04 11:08:05 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include <stdbool.h>

bool	strings_are_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (false);
	while (s1[i])
	{
		if (!s2[i])
			return (false);
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s2[i])
		return (false);
	return (true);
}
