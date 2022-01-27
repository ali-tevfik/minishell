/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/27 12:30:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_command	*create_command(t_redir_type redir_in, t_redir_type redir_out, 
							char *in_file, char *out_file, 
							size_t len_command, ...)
{
	t_command	*command;
	va_list		ap;
	size_t		i;

	command = ft_calloc(1, sizeof(t_command));
	command->command = ft_calloc(len_command, sizeof(char *));
	command->in_file = in_file;
	command->out_file = out_file;
	command->redirection_operator_in = redir_in;
	command->redirection_operator_out = redir_out;

	i = 0;
	va_start(ap, len_command);
	while (i < len_command)
	{
		command->command[i] = ft_strdup(va_arg(ap, char *));
		i++;
	}
	command->command[i] = NULL;
	va_end(ap);
	return (command);
}

void	free_command(void *command)
{
	size_t		i;
	t_command 	*casted_command;

	i = 0;
	casted_command = (t_command *)command;
	while (casted_command->command[i] != NULL)
	{
		free(casted_command->command[i]);
		i++;
	}
	free(casted_command->command);
	free(casted_command->in_file);
	free(casted_command->out_file);
	free(casted_command);
}

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