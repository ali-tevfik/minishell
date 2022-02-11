/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:37:50 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/11 19:43:52 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../incl/built_in.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"

#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/parser/create_parse_list.h"


t_list	*expected_list;
t_list	*actual_list;

TEST_GROUP(export);

TEST_SETUP(export)
{
	expected_list = NULL;
	actual_list = NULL;
}

TEST_TEAR_DOWN(export)
{
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

TEST(export, ExportOneVariable)
{

}
