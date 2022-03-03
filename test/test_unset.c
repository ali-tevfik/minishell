/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_unset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 17:49:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/03 13:35:02 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../incl/built_in.h"

/* User defined headers */
#include "../incl/minishell.h"
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/parser/create_parse_list.h"
#include "utils.h"

/* Variables */
static t_list	*token_list;
static t_list	*parse_list;
static t_list	*env_list;
static t_list	*expected_env;
static t_list	*actual_env;
static char		*env[] = {	"SHELL=/bin/zsh",
							"SYSTEM=LINUX",
							"LOGNAME=hyilmaz",
							NULL,
						};

TEST_GROUP(UnsetBuiltin);

TEST_SETUP(UnsetBuiltin)
{
	token_list = NULL;
	parse_list = NULL;
	env_list = create_env_list(env);
}

TEST_TEAR_DOWN(UnsetBuiltin)
{
}

TEST(UnsetBuiltin, DeleteFromMiddle)
{
	char	*input = "unset SYSTEM";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(4, "SHELL", "/bin/zsh", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, DeleteLast)
{
	char	*input = "unset LOGNAME";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(4, "SHELL", "/bin/zsh", "SYSTEM", "LINUX");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, DeleteFirst)
{
	char	*input = "unset SHELL";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(4, "SYSTEM", "LINUX", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, DeleteAll)
{
	char	*input = "unset SHELL SYSTEM LOGNAME";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(0);

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare both lists are NULL */
	TEST_ASSERT_NULL(expected_env);
	TEST_ASSERT_NULL(actual_env);
}

TEST(UnsetBuiltin, DeleteAllAndExtra)
{
	char	*input = "unset SHELL SYSTEM LOGNAME HILMI";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(0);

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare both lists are NULL */
	TEST_ASSERT_NULL(expected_env);
	TEST_ASSERT_NULL(actual_env);
}

TEST(UnsetBuiltin, NonExisting0)
{
	char	*input = "unset HILMI";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(6, "SHELL", "/bin/zsh", "SYSTEM", "LINUX", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, NonExisting1)
{
	char	*input = "unset SHELLL";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(6, "SHELL", "/bin/zsh", "SYSTEM", "LINUX", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, NoArgument)
{
	char	*input = "unset";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(6, "SHELL", "/bin/zsh", "SYSTEM", "LINUX", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(UnsetBuiltin, WrongArgument)
{
	char	*input = "unset asgadg sg fhdfhdh -d fgdfg-g-df-gg";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = create_environment_list(6, "SHELL", "/bin/zsh", "SYSTEM", "LINUX", "LOGNAME", "hyilmaz");

	/* Actual environment list */
	actual_env = env_list;
	unset_command(&actual_env, (t_pipeline *)(parse_list->content));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}