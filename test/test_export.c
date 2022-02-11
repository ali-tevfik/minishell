/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:37:50 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/11 14:52:04 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../incl/commands.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"
#include "utils.h"

#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/parser/create_parse_list.h"

t_list	*token_list;
t_list	*parse_list;
t_list	*env_list;

t_list	*env_variable;
t_list	*expected_env;
t_list	*actual_env;


static char			*env[] = {	"SHELL=/bin/zsh",
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
	env_list = add_envp(env);
}

TEST_TEAR_DOWN(ExportBuiltin)
{
	// free expected_env
	// free actual_env
	// free token_list
	// free parse_list
}

TEST(ExportBuiltin, ExportOneVariable)
{
	char	*input = "export ali=hilmi";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	t_env	*env_variable = ft_calloc(1, sizeof(*env_variable));
	env_variable->key = ft_strdup("ali");
	env_variable->value = ft_strdup("hilmi");
	t_list *expected_env = copy_environment_linked_list(env_list);
	ft_lstadd_back(&expected_env, ft_lstnew(env_variable));

	/* Actual environment list */
	t_list	*actual_env = env_list;
	export_command(&actual_env, ((t_pipeline *)(parse_list->content)));

	/* Compare length linked lists */
	int	len_expected_list = ft_lstsize(expected_env);
	int	len_actual_list = ft_lstsize(actual_env);
	TEST_ASSERT_EQUAL_INT(len_expected_list, len_actual_list);

	/* Compare elements of linked list */
	compare_environment_lists(expected_env, actual_env);
}


// TEST(export, add_normal)
// {
// 	t_list	*input_list = NULL;

// 	/* Actual List */
// 	export_command(&input_list,"export hello=codam");
// 	export_command(&input_list,"export codam=42");
// 	export_command(&input_list,"export coding=15");
// 	export_command(&input_list,"export college=as");

// 	/* Expected list (Removing 3rd element) */
// 	t_env *env;

// 	/* Input list */
// 	env = ft_calloc(1,sizeof(*env));
// 	env->key = ft_strdup("hello");
// 	env->value = ft_strdup("codam");
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(1,sizeof(*env));
// 	env->key = ft_strdup("codam");
// 	env->value = ft_strdup("42");
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(1,sizeof(*env));
// 	env->key = ft_strdup("coding");
// 	env->value = ft_strdup("15");
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(1,sizeof(*env));
// 	env->key = ft_strdup("college");
// 	env->value = ft_strdup("as");
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	/* Compare contents */
// 	while (expected_list)
// 	{
// 		TEST_ASSERT_EQUAL_STRING(((t_env *)expected_list->content)->key, ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING(((t_env *)expected_list->content)->value, ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}
// }

// TEST(export, wrong)
// {
// 	t_list	*input_list = NULL;

// 	export_command(&input_list,"export hello");
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{
// 		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }

// TEST(export, check_tab)
// {
// 	t_list	*input_list = NULL;
// 	t_env *env;

// 	export_command(&input_list,"export 			hello=codam");

// 	/* Expected list (Removing 3rd element) */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{
// 		TEST_ASSERT_EQUAL_STRING(((t_env *)expected_list->content)->key, ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING(((t_env *)expected_list->content)->value, ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}
// }