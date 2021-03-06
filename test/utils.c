/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:28:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 19:13:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Compare token lists.
*/

void	compare_token_lists(t_list *expected_list, t_list *actual_list)
{
	t_token	*expected_token;
	t_token	*actual_token;

	TEST_ASSERT_EQUAL_size_t(ft_lstsize(expected_list), ft_lstsize(actual_list));

	while (expected_list != NULL)
	{
		expected_token = expected_list->content;
		actual_token = actual_list->content;
		TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
		TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);
		expected_list = expected_list->next;
		actual_list = actual_list->next;
	}
}

/*
** Create a command from the inputs.
**
*/

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

/*
** Give va_args as pairs like: 
** create_redirection_list(4, 1_file_in, READ, 2_file_out, OUT);
** 1_file_in is redirected with READ operator.
*/

t_list	*create_redirection_list(size_t total_redir_operators_plus_filenames, ...)
{
	t_list			*redirection_list;
	va_list			ap;
	size_t			i;
	size_t			total_redirections;
	t_redirection	*redir_element;

	if (total_redir_operators_plus_filenames == 0)
		return (NULL);
	i = 0;
	redirection_list = NULL;
	total_redirections = total_redir_operators_plus_filenames / 2;
	va_start(ap, total_redir_operators_plus_filenames);
	while (i < total_redirections)
	{
		redir_element = ft_calloc(1, sizeof(t_redirection));
		redir_element->file = ft_strdup(va_arg(ap, char *));
		redir_element->redir_type = va_arg(ap, size_t);
		ft_lstadd_back(&redirection_list, ft_lstnew(redir_element));
		i++;
	}
	va_end(ap);
	return (redirection_list);
}

t_pipeline	*create_pipeline_element(char **command, t_list *redirection)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(*pipeline));
	pipeline->command = command;
	pipeline->redirection = redirection;
	return (pipeline);
}

void	free_command(char **command)
{
	size_t	i;

	i = 0;
	while (command[i] != NULL)
	{
		free(command[i]);
		i++;
	}
	free(command);
}

static void	free_redirection(void *redirection)
{
	t_redirection *casted_redir;

	casted_redir = redirection;
	free(casted_redir->file);
}

void	free_pipeline(void *pipeline)
{
	t_pipeline	*casted_pipeline;

	casted_pipeline = pipeline;
	free_command(casted_pipeline->command);							/* Free command */
	ft_lstclear(&casted_pipeline->redirection, free_redirection);	/* Free redirection linked list */
	free(casted_pipeline);
}

void	compare_pipelines(t_pipeline *expected_pipeline, t_pipeline *actual_pipeline)
{
	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_pipeline->command);
	size_t	expected_len = len_string_array(expected_pipeline->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_pipeline->command, actual_pipeline->command, expected_len);

	/* Compare redirection lists */
	t_list	*expected_redir_list = expected_pipeline->redirection;
	t_list	*actual_redir_list = actual_pipeline->redirection;
	size_t	len_expected = ft_lstsize(expected_redir_list);
	size_t	len_actual = ft_lstsize(actual_redir_list);
	TEST_ASSERT_EQUAL_size_t(len_expected, len_actual);

	while (expected_redir_list != NULL)
	{
		TEST_ASSERT_EQUAL_STRING(((t_redirection *)(expected_redir_list->content))->file, ((t_redirection *)(actual_redir_list->content))->file);
		TEST_ASSERT_EQUAL_INT(((t_redirection *)(expected_redir_list->content))->redir_type, ((t_redirection *)(actual_redir_list->content))->redir_type);
		expected_redir_list = expected_redir_list->next;
		actual_redir_list = actual_redir_list->next;
	}
}

size_t	len_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
		i++;
	return (i);
}

void	print_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
	{
		printf("%s\n", string_array[i]);
		i++;
	}
}

t_list	*copy_environment_linked_list(t_list *env_list)
{
	t_list	*copied_list;
	t_env	*env_variable;

	copied_list = NULL;
	while (env_list != NULL)
	{
		env_variable = ft_calloc(1, sizeof(*env_variable));
		env_variable->key = ft_strdup(((t_env *)(env_list->content))->key);
		env_variable->value = ft_strdup(((t_env *)(env_list->content))->value);
		ft_lstadd_back(&copied_list, ft_lstnew(env_variable));
		env_list = env_list->next;
	}
	return (copied_list);
}

void	compare_environment_lists(t_list *expected_env_list, t_list *actual_env_list)
{
	char	*expected_key;
	char	*expected_value;
	char	*actual_key;
	char	*actual_value;
	
	while (expected_env_list != NULL)
	{
		expected_key = ((t_env *)(expected_env_list->content))->key;
		expected_value = ((t_env *)(expected_env_list->content))->value;
		actual_key = ((t_env *)(actual_env_list->content))->key;
		actual_value = ((t_env *)(actual_env_list->content))->value;
		TEST_ASSERT_EQUAL_STRING(expected_key, actual_key);
		TEST_ASSERT_EQUAL_STRING(expected_value, actual_value);
		expected_env_list = expected_env_list->next;
		actual_env_list = actual_env_list->next;
	}
}

t_env	*create_env_variable(char *key, char *value)
{
	t_env	*env_variable;

	env_variable = ft_calloc(1, sizeof(*env_variable));
	env_variable->key = strdup(key);
	env_variable->value = strdup(value);
	return (env_variable);
}

void	free_env_variable(void *environment_variable)
{
	t_env	*casted_env_variable;

	casted_env_variable = environment_variable;
	free(casted_env_variable->key);
	free(casted_env_variable->value);
	free(casted_env_variable);
}

/*
** Create an environment list.
** Each element of the linked list contains t_env *
*/
t_list	*create_environment_list(int len, ...)
{
	int		i;
	t_list	*env_list;
	va_list	ap;
	t_env	*env_variable;

	i = 0;
	env_list = NULL;
	va_start(ap, len);
	while (i < len / 2)
	{
		env_variable = ft_calloc(1, sizeof(*env_variable));
		env_variable->key = ft_strdup(va_arg(ap, char *));
		env_variable->value = ft_strdup(va_arg(ap, char *));
		ft_lstadd_back(&env_list, ft_lstnew(env_variable));
		i++;
	}
	va_end(ap);
	return (env_list);
}
