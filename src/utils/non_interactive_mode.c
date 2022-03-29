/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_interactive_mode.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 18:53:46 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/29 12:26:40 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/protect.h"
#include "../parser/create_parse_list.h"
#include "../tokenizer/tokenizer.h"
#include "../libft/libft.h"
#include <stdlib.h>

/*
** This function handles the case where -c is given as an option.
** Very useful when compares minishell to bash in a tester.
*/

void	read_commands_from_string(int argc, char **argv, t_list **env_list,
	int last_exit_status)
{
	if (argc < 3)
		return ;
	if (!strings_are_equal(argv[1], "-c"))
	{
		printf("Error: Run as ./minishell -c \"command_to_execute\"");
		exit (1);
	}
	last_exit_status = tokenize_parse_execute(argv[2], env_list,
			last_exit_status);
	exit(last_exit_status);
}
