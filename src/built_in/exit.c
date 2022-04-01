/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:09:36 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:49:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/built_in_utils.h"
#include "../../incl/minishell.h"
#include "../parser/create_parse_list.h"

bool	return_value_check_int(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_command(t_pipeline *pipeline, int *exit_code)
{
	if (!pipeline->command[1])
	{
		ft_putendl_fd("exit", STDIN_FILENO);
		exit((unsigned char)*exit_code);
	}
	else if (pipeline->command[2]
		&& return_value_check_int(pipeline->command[1]))
		print_error("exit", "too many arguments");
	else
	{
		if (!return_value_check_int(pipeline->command[1]))
		{
			print_error("exit", "numeric argument required");
			*exit_code = 255;
			exit((unsigned char)255);
		}
		*exit_code = ft_atoi(pipeline->command[1]);
		ft_putendl_fd("exit", STDIN_FILENO);
		exit((unsigned char)*exit_code);
	}
}
