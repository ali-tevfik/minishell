/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 18:30:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	compare_command_structs(t_command *expected_command, t_command *actual_command)
{
	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

size_t	len_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
		i++;
	return (i);
}