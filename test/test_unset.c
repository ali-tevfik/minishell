#include "unity_fixture.h"
#include "../incl/built_in.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"


// t_list	*expected_list;
// t_list	*actual_list;


// TEST_GROUP(unset);

// TEST_SETUP(unset)
// {
// 	expected_list = NULL;
// 	actual_list = NULL;
// }

// TEST_TEAR_DOWN(unset)
// {
// }

// TEST(unset,delete_third)
// {
// 	t_list	*input_list = NULL;
// 	t_env *env;

// 	/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* Expected list (Removing 3rd element) */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	//codam

// 	/* My list */
// 	unset_command(&input_list,"unset coding");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{

// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }




// TEST(unset,delete_first)
// {
// 		t_list	*input_list = NULL;
// 		t_env *env;

// 	/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* Expected list (Removing 3rd element) */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	/* My list */
// 	unset_command(&input_list,"unset hello");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{

// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }





// TEST(unset,delete_last)
// {
// 		t_list	*input_list = NULL;
// 		t_env *env;

// 	/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* Expected list (Removing 3rd element) */

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));



// 	//codam

// 	/* My list */
// 	unset_command(&input_list,"unset amsterdam");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }





// TEST(unset,delete_nooit)
// {
// 		t_list	*input_list = NULL;
// 	t_env *env;
// 		/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* Expected list (Removing 3rd element) */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&expected_list, ft_lstnew(env));

// 	//codam

// 	/* My list */
// 	unset_command(&input_list,"unset null");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{

// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }




// TEST(unset,delete_all)
// {
// 		t_list	*input_list = NULL;
// 		t_env *env;

// 	/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* My list */
// 	unset_command(&input_list,"unset hello");
// 	unset_command(&input_list,"unset codam");
// 	unset_command(&input_list,"unset coding");
// 	unset_command(&input_list,"unset amsterdam");
// 	unset_command(&input_list,"unset college");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{

// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }




// TEST(unset,delete_all_and_extra)
// {
// 		t_list	*input_list = NULL;
// 	t_env *env;

// 	/* Input list */
// 		/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));;

// 	/* Expected list (NULL) */

// 	/* My list */
// 	unset_command(&input_list,"unset hello");
// 	unset_command(&input_list,"unset codam");
// 	unset_command(&input_list,"unset coding");
// 	unset_command(&input_list,"unset amsterdam");
// 	unset_command(&input_list,"unset college");
// 	unset_command(&input_list,"unset ajjkasfjk");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{

// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }




// TEST(unset,export_and_delete)
// {
// 	t_env *env;
// 		t_list	*input_list = NULL;

// 	/* Input list */
// 		/* Input list */
// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "hello";
// 	env->value = "codam";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "codam";
// 	env->value = "42";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "coding";
// 	env->value = "15";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "college";
// 	env->value = "as";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	env = ft_calloc(2,sizeof(env));
// 	env->key = "amsterdam";
// 	env->value = "asfsfasfas";
// 	ft_lstadd_back(&input_list, ft_lstnew(env));

// 	/* Expected list (NULL) */

// 	/* My list */
// 	unset_command(&input_list,"unset hello");
// 	unset_command(&input_list,"unset codam");
// 	unset_command(&input_list,"unset coding");
// 	unset_command(&input_list,"unset amsterdam");
// 	unset_command(&input_list,"unset college");
// 	unset_command(&input_list,"unset ajjkasfjk");
// 	export_command(&input_list,"export asfjaskl=jkahsjfhjkasfj");
// 	unset_command(&input_list,"unset asfjaskl");

// 	/* Compare length of lists */
// 	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

// 	/* Compare contents */
// 	while (expected_list)
// 	{
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->key), ((t_env *)input_list->content)->key);
// 		TEST_ASSERT_EQUAL_STRING((( (t_env*)expected_list->content)->value), ((t_env *)input_list->content)->value);
// 		expected_list = expected_list->next;
// 		input_list = input_list->next;
// 	}

// }
