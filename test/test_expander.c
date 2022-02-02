#include "unity_fixture.h"
#include "../incl/commands.h"
#include "../incl/minishell.h"
#include "../src/libft/libft.h"


t_list	*input_list;
t_env *env;
TEST_GROUP(expander);

TEST_SETUP(expander)
{

	/* Input list */
	env = ft_calloc(2,sizeof(env));
	env->key = "COLORFGBG";
	env->value = "7;0";
	ft_lstadd_back(&input_list, ft_lstnew(env));

	env = ft_calloc(2,sizeof(env));
	env->key = "TERM_PROGRAM";
	env->value = "vscode";
	ft_lstadd_back(&input_list, ft_lstnew(env));

	env = ft_calloc(2,sizeof(env));
	env->key = "PWD";
	env->value = "/Users/adoner/Desktop/minishell/orginal";
	ft_lstadd_back(&input_list, ft_lstnew(env));

	env = ft_calloc(2,sizeof(env));
	env->key = "_";
	env->value = "/usr/bin/env";
	ft_lstadd_back(&input_list, ft_lstnew(env));

	env = ft_calloc(2,sizeof(env));
	env->key = "PATH";
	env->value = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	ft_lstadd_back(&input_list, ft_lstnew(env));
}

TEST_TEAR_DOWN(expander)
{
}

TEST(expander, expander_find_second)
{
	char *result = expander("TERM_PROGRAM", input_list);
	// printf("result = %s\n",result);
	TEST_ASSERT_EQUAL_STRING(result, "vscode");
}

TEST(expander, expander_find_last)
{
	char *result = expander("PATH", input_list);
	// printf("result = %s\n",result);
	TEST_ASSERT_EQUAL_STRING(result, "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
}

TEST(expander, expander_find_middle)
{
	char *result = expander("PWD", input_list);
	// printf("result = %s\n",result);
	TEST_ASSERT_EQUAL_STRING(result, "/Users/adoner/Desktop/minishell/orginal");
}

TEST(expander, expander_find_first)
{
	char *result = expander("COLORFGBG", input_list);
	// printf("result = %s\n",result);
	TEST_ASSERT_EQUAL_STRING(result, "7;0");
}
TEST(expander, expander_dont_find)
{
	char *result = expander("deneme", input_list);
	// printf("result = %s\n",result);
	TEST_ASSERT_EQUAL_STRING(result, NULL);
}

