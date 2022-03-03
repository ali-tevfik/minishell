/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:37:50 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/03 13:34:56 by hyilmaz       ########   odam.nl         */
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
#include "../src/tokenizer/remove_quotes_from_all_tokens.h"
#include "utils.h"

/* Variables */
static t_list	*token_list;
static t_list	*parse_list;
static t_list	*env_list;
static t_list	*expected_env;
static t_list	*actual_env;
static t_env	*env_variable;
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							NULL,
						};

TEST_GROUP(ExportBuiltin);

TEST_SETUP(ExportBuiltin)
{
	token_list = NULL;
	parse_list = NULL;
	env_list = create_env_list(env);
}

TEST_TEAR_DOWN(ExportBuiltin)
{
	// ft_lstclear(&expected_env, free_env_variable);
	// ft_lstclear(&actual_env, free_env_variable);
	// ft_lstclear(&parse_list, free_pipeline);
	// ft_lstclear(&token_list, free_token);
}

TEST(ExportBuiltin, ExportOneVariable)
{
	char	*input = "export ali=hilmi";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);
	
	env_variable = create_env_variable("ali", "hilmi");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportTwoVariables)
{
	char	*input = "export ali=hilmi codam=amsterdam";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("ali", "hilmi");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	env_variable = create_env_variable("codam", "amsterdam");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportThreeVariables)
{
	char	*input = "export ali=hilmi codam=amsterdam utrecht=nl";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("ali", "hilmi");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	env_variable = create_env_variable("codam", "amsterdam");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	env_variable = create_env_variable("utrecht", "nl");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportSameVariableAssignment0)
{
	char	*input = "export ali=hilmi ali=haha";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("ali", "haha");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportSameVariableAssignment1)
{
	char	*input = "export ali=hilmi codam=amsterdam ali=haha";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("codam", "amsterdam");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	env_variable = create_env_variable("ali", "haha");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportNoInput)
{
	char	*input = "export";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportAssignEmpty0)
{
	char	*input = "export codam=";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("codam", "");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportAssignEmpty1)
{
	char	*input = "export codam=\"\"";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("codam", "");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportVariableNameStartsWithUnderscore)
{
	char	*input = "export _codam=amsterdam";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("_codam", "amsterdam");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportVariableNameAndValueStartsWithUnderscore)
{
	char	*input = "export _ali=_yoo";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("_ali", "_yoo");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportAssignWithSpaceBeforeEqualSign)
{
	char	*input = "export codam =hilmiyilmaz";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportAssignWithSpaceAfterEqualSign)
{
	char	*input = "export codam= hilmiyilmaz";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("codam", "");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportAssignWithSpaceBeforeAndAfterEqualSign)
{
	char	*input = "export codam = hilmiyilmaz";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportCaseSensitivity)
{
	char	*input = "export No=10 no=11";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("No", "10");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	env_variable = create_env_variable("no", "11");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportInvalidOption)
{
	char	*input = "export -hilmiadsdas=yilmaz=abi_len";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportSpaceInValue)
{
	char	*input = "export helloworld=\"ali doner codam\"";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("helloworld", "ali doner codam");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportUnderScoreAsKey)
{
	char	*input = "export _=ali";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("_", "ali");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}

TEST(ExportBuiltin, ExportWithExpansion0)
{
	char	*input = "export hilmi=ali$LOGNAME";

	/* Tokenize and parse */
	char	*expanded_input = check_expander(input, env_list);
	token_list = tokenize_input(expanded_input);
	remove_quotes_from_all_tokens(token_list);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	env_variable = create_env_variable("hilmi", "alihyilmaz");
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
	
	free(expanded_input);
}