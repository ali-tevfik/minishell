#include "unity_fixture.h"
#include "../incl/commands.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"


t_list	*expected_list;
t_list	*actual_list;


TEST_GROUP(unset);

TEST_SETUP(unset)
{
	expected_list = NULL;
	actual_list = NULL;
}

TEST_TEAR_DOWN(unset)
{
}

TEST(unset,delete_third)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam")));


	//codam

	/* My list */
	unset_command(&input_list,"unset coding");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}

TEST(unset,delete_first)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam")));

	/* My list */
	unset_command(&input_list,"unset hello");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}



TEST(unset,delete_last)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));


	//codam

	/* My list */
	unset_command(&input_list,"unset amsterdam");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}



TEST(unset,delete_nooit)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam")));


	//codam

	/* My list */
	unset_command(&input_list,"unset null");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}



TEST(unset,delete_all)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (NULL) */

	/* My list */
	unset_command(&input_list,"unset hello");
	unset_command(&input_list,"unset codam");
	unset_command(&input_list,"unset coding");
	unset_command(&input_list,"unset amsterdam");
	unset_command(&input_list,"unset college");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}



TEST(unset,delete_all_and_extra)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (NULL) */

	/* My list */
	unset_command(&input_list,"unset hello");
	unset_command(&input_list,"unset codam");
	unset_command(&input_list,"unset coding");
	unset_command(&input_list,"unset amsterdam");
	unset_command(&input_list,"unset college");
	unset_command(&input_list,"unset ajjkasfjk");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}




TEST(unset,export_and_delete)
{
		t_list	*input_list = NULL;

	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (NULL) */

	/* My list */
	unset_command(&input_list,"unset hello");
	unset_command(&input_list,"unset codam");
	unset_command(&input_list,"unset coding");
	unset_command(&input_list,"unset amsterdam");
	unset_command(&input_list,"unset college");
	unset_command(&input_list,"unset ajjkasfjk");
	export_command(&input_list,"export asfjaskl=jkahsjfhjkasfj");
	unset_command(&input_list,"unset asfjaskl");

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}

}
