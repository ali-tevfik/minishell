/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expand_single_variable.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 18:50:13 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/18 14:59:35 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/expander/expand_single_variable.h"

/* System headers */
#include <string.h>
#include <sys/utsname.h>

/* User defined headers */
#include "../src/libft/libft.h"
#include "utils.h"

/* Variables */
static char		*actual_expansion;
static char		*expected_expansion;;
static t_list	*env_list;
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"HOME=/home/hilmi",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							"a=b",
							NULL,
						};

/*
** Tests:
** $HOME_
** $HOME+
** $HOME+++
** $+HOME
**
**
**
**
**
**
**
**
*/


TEST_GROUP(ExpandSingleVariable);

TEST_SETUP(ExpandSingleVariable)
{
	env_list = add_envp(env);
	actual_expansion = NULL;
}

TEST_TEAR_DOWN(ExpandSingleVariable)
{
	free(actual_expansion);
	free(expected_expansion);
}

TEST(ExpandSingleVariable, Existing0)
{
	char	*input = "$HOME";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("/home/hilmi");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}

TEST(ExpandSingleVariable, Existing1)
{
	char	*input = "$LOGNAME";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("hyilmaz");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}


TEST(ExpandSingleVariable, Existing2)
{
	char	*input = "$DISPLAY";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}

TEST(ExpandSingleVariable, Existing3)
{
	char	*input = "$LOGNAME+";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("hyilmaz+");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}

TEST(ExpandSingleVariable, NonExisting0)
{
	char	*input = "$DISPLAYY";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}

TEST(ExpandSingleVariable, NonExisting1)
{
	char	*input = "$hahah";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}

TEST(ExpandSingleVariable, NonExisting2)
{
	char	*input = "$+LOGNAME";

	/* Actual expansion */
	actual_expansion = expand_single_variable(env_list, input, strlen(input));

	/* Expected expansion */
	expected_expansion = ft_strdup("$+LOGNAME");

	/* Compare outputs */
	TEST_ASSERT_EQUAL_STRING(expected_expansion, actual_expansion);
}
