#include "unity_fixture.h"
#include "../incl/commands.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"



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


TEST(export, add_normal)
{
	t_list	*input_list = NULL;

	export_command(&input_list,"export hello=");
	export_command(&input_list,"export codam=");
	export_command(&input_list,"export college=");
	export_command(&input_list,"export amsterdam=");

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello=")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam=")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college=")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam=")));
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}
}

TEST(export, wrong)
{
	t_list	*input_list = NULL;

	export_command(&input_list,"export hello");
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}


TEST(export, check_tab)
{
	t_list	*input_list = NULL;

	export_command(&input_list,"export 			hello=");

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello=")));
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}
}
