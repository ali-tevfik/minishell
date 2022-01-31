/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_space.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:55:55 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/31 15:33:47 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

int	skip_space_start(char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == '\t' || *(s + i) == '\n' || *(s + i) == '\f'
			|| *(s + i) == '\r' || *(s + i) == '\v' || *(s + i) == ' ')
			i++;
		else
			break ;
	}
	return (i);
}

int	skip_space_end(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == '\t' || *(s + i) == '\n' || *(s + i) == '\f'
			|| *(s + i) == '\r' || *(s + i) == '\v' || *(s + i) == ' ')
			i--;
		else
			break ;
	}
	return (i);
}

char	*skip_space(char *s)
{
	char	*new;
	int		start;
	int		end;

	start = skip_space_start(s);
	end = skip_space_end(s);
	new = ft_substr(s, start, end - start + 1);
	if (!new)
		exit(0);
	return (new);
}


int		find_space(char *txt)
{
	int i;

	i = 0;
	printf("gelen txt [%s]\n", txt);
	while (txt[i])
	{
		if (txt[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}
