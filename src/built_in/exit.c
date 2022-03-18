/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/16 19:41:20 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/create_parse_list.h"

bool return_value_check_int(char *c)
{
	int	i;

	i = 0;
	while(c[i])
	{
		if (!ft_isdigit(c[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_command(t_pipeline *pipeline)
{
	int	return_value;

	if (!pipeline->command[1])
		exit(1);
	else if (pipeline->command[2] && return_value_check_int(pipeline->command[1]))
	{
		printf("Minishell: exit: too many arguments\n");
	}
	else
	{
		if (!return_value_check_int(pipeline->command[1]))
		{
			printf("Minishell: exit: %s: numeric argument required\n", pipeline->command[0]);
			exit(255);
		}
		return_value = ft_atoi(pipeline->command[0]);
		printf("%d\n",return_value);
		exit(return_value);
	}

}
