/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/04 11:57:29 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Give va_args as pairs like: 
** create_redirection_list(4, 1_file_in, READ, 2_file_out, OUT);
** 1_file_in is redirected with READ operator.
*/

t_redirection	*create_redirection_list(size_t total_redir_operators_plus_filenames, ...)
{
	t_list			*redirection_list;
	va_list			ap;
	size_t			i;
	size_t			total_redirections;
	t_redirection	*redir_element;

	i = 0;
	redirection_list = NULL;
	total_redirections = total_redir_operators_plus_filenames / 2;
	redir_element = ft_calloc(1, sizeof(t_redirection));
	ve_start(ap, total_redir_operators_plus_filenames);
	while (i < total_redirections)
	{
		redir_element->file = va_arg(ap, char *);
		redir_element->redir_type = va_arg(ap, size_t);
		ft_lstadd_back(&redirection_list, ft_lstnew(redir_element));
		i++;
	}
	va_end(ap);
	return (redirection_list);
}

char	**create_command(size_t len_command, ...)
{
	char		**command;
	va_list		ap;
	size_t		i;

	i = 0;
	command = ft_calloc(len_command + 1, sizeof(char *));
	va_start(ap, len_command);
	while (i < len_command)
	{
		command[i] = ft_strdup(va_arg(ap, char *));
		i++;
	}
	command[i] = NULL;
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