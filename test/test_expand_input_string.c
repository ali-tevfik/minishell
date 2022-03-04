/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expand_input_string.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 11:20:53 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/04 12:19:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../incl/minishell.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "utils.h"

/* Variables */
static char	*actual_expansion;
static char	*expected_expansion;
static t_list	*env_list;
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"HOME=/home/hilmi",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							"a=b",
							"hilmi_8=bro",
							"codam_=",
							"test=hilmi yilmaz",
							"hilmi=ho -n",
							NULL,
						};

TEST_GROUP(ExpandInputString);

TEST_SETUP(ExpandInputString)
{
	env_list = create_env_list(env);
	actual_expansion = NULL;
	expected_expansion = NULL;
}

TEST_TEAR_DOWN(ExpandInputString)
{
	ft_lstclear(&env_list, free_env_variable);
	free(actual_expansion);
	free(expected_expansion);
}

TEST(ExpandInputString, SingleVariableExisting0)
{
	char	*input = "$HOME";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("/home/hilmi");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$HOME\"");
}

TEST(ExpandInputString, SingleVariableExisting1)
{
	char	*input = "$LOGNAME";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("hyilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$LOGNAME\"");
}

TEST(ExpandInputString, SingleVariableExisting2)
{
	char	*input = "$DISPLAY";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$DISPLAY\"");
}

TEST(ExpandInputString, SingleVariableExisting3)
{
	char	*input = "$LOGNAME+";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("hyilmaz+");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$LOGNAME+\"");
}

TEST(ExpandInputString, SingleVariableExisting4)
{
	char	*input = "$a";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("b");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$a\"");
}

TEST(ExpandInputString, SingleVariableExisting5)
{
	char	*input = "$a  ";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("b  ");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$a  \"");
}

TEST(ExpandInputString, SingleVariableExisting6)
{
	char	*input = "$a!";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("b!");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$a!\"");
}

TEST(ExpandInputString, SingleVariableExisting7)
{
	char	*input = "$hilmi_8";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("bro");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$hilmi_8\"");
}

TEST(ExpandInputString, SingleVariableExisting8)
{
	char	*input = "$codam_";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$codam_\"");
}

TEST(ExpandInputString, SingleVariableExisting9)
{
	char	*input = "$codam_-";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("-");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$codam_-\"");
}

TEST(ExpandInputString, SingleVariableExisting10)
{
	char	*input = "\"$hilmi_8-\"";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("\"bro-\"");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"\"$hilmi_8-\"\"");
}

TEST(ExpandInputString, SingleVariableExisting11)
{
	// TEST_IGNORE();
	char	*input = "\'$hilmi_8-\'";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("\'$hilmi_8-\'");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"\'$hilmi_8-\'\"");
}

TEST(ExpandInputString, SingleVariableNonExisting0)
{
	char	*input = "$DISPLAYY";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$DISPLAYY\"");
}

TEST(ExpandInputString, SingleVariableNonExisting1)
{
	char	*input = "$hahahahah";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$hahahahah\"");
}

TEST(ExpandInputString, SingleVariableNonExisting2)
{
	char	*input = "$hahahahah&";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("&");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$hahahahah&\"");
}

TEST(ExpandInputString, SingleVariableNonExisting3)
{
	char	*input = "$+LOGNAME";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$+LOGNAME");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$+LOGNAME\"");
}

TEST(ExpandInputString, SingleVariableNonExisting4)
{
	char	*input = "$ LOGNAME";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$ LOGNAME");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$ LOGNAME\"");
}

TEST(ExpandInputString, SingleVariableNonExisting5)
{
	char	*input = "$";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$\"");
}

TEST(ExpandInputString, SingleVariableNonExisting6)
{
	char	*input = "$$";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$$");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$$\"");
}

TEST(ExpandInputString, SingleVariableNonExisting7)
{
	char	*input = "$\"LOGNAME\"";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$\"LOGNAME\"");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$\"LOGNAME\"\"");
}

TEST(ExpandInputString, SingleVariableNonExisting8)
{
	// TEST_IGNORE();
	char	*input = "$\'LOGNAME\'";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("$\'LOGNAME\'");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"$\'LOGNAME\'\"");
}

TEST(ExpandInputString, SingleVariableNonExisting9)
{
	char	*input = "\"\"$HO\"ME\"";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("\"\"\"ME\"");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"\"\"$HO\"ME\"");
}

TEST(ExpandInputString, MultipleVariables0)
{
	char	*input = "cat -c $hilmi_8";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("cat -c bro");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"cat -c $hilmi_8\"");
}

TEST(ExpandInputString, MultipleVariables1)
{
	char	*input = "echo $test";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("echo hilmi yilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"echo $test\"");
}

TEST(ExpandInputString, MultipleVariables2)
{
	char	*input = "ec$hilmi $test";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("echo -n hilmi yilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"ec$hilmi $test\"");
}

TEST(ExpandInputString, MultipleVariables3)
{
	char	*input = "ec\"$hilmi\" $test";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("ec\"ho -n\" hilmi yilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"ec$hilmi $test\"");
}

TEST(ExpandInputString, MultipleVariables4)
{
	// TEST_IGNORE();
	char	*input = "ec\'$hilmi\' $test";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("ec\'$hilmi\' hilmi yilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"ec\'$hilmi\' $test\"");
}

TEST(ExpandInputString, MultipleVariables5)
{
	char	*input = "ec$hilmi$test $LOGNAME\"$HOME\"";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("echo -nhilmi yilmaz hyilmaz\"/home/hilmi\"");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"ec$hilmi$test $LOGNAME\"$HOME\"\"");
}

TEST(ExpandInputString, MultipleVariables6)
{
	char	*input = "\"\"$HO\"ME\"";

	/* Actual expansion */
	actual_expansion = expand_input_string(input, env_list);

	/* Expected expansion */
	expected_expansion = ft_strdup("echo -nhilmi yilmaz hyilmaz\"/home/hilmi\"");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_expansion, actual_expansion, "input = \"ec$hilmi$test $LOGNAME\"$HOME\"\"");
}
