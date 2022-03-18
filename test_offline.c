/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_offline.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 18:53:46 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/18 14:55:36 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"
#include "incl/protect.h"
#include "src/parser/create_parse_list.h"
#include "src/tokenizer/tokenizer.h"
#include "src/libft/libft.h"

#include <stdlib.h>

// void read_commands_from_string(int argc, char **argv, t_list **env_list, int exit_code)
// {
// 	if (argc < 3)
// 		return ;
// 	if (!strings_are_equal(argv[1], "-c"))
// 	{
// 		printf("Error: Run as ./minishell -c \"command_to_execute\"");
// 		exit (1);
// 	}
// 	char *expanded_line = expand_input_string(argv[2], *env_list, exit_code);
// 	int last_exit_status = tokenize_parse_execute(expanded_line, env_list);
// 	exit(last_exit_status);
// }
