/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_name_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:26:30 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/15 15:35:19 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

int	ft_isname(char *txt)
{
	int	i;

	i = 1;
	if (!txt)
		return (0);
	if (!(ft_isalpha(txt[0]) || txt[0] == '_'))
		return (0);
	while (txt[i])
	{
		if (!(ft_isalnum(txt[i]) || txt[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
