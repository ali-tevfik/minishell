/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_word.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:38:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 17:11:44 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_word.h"

/* System headers */
#include <stdlib.h>

/* User defined headers */
#include "utils.h"

t_token		*actual_token;
t_token		*expected_token;
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

TEST_GROUP(TokenizeWord);

TEST_SETUP(TokenizeWord)
{
	env_list = create_env_list(env);
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizeWord)
{
	free(expected_token);
	free(actual_token);
	ft_lstclear(&env_list, free_env_variable);
}

TEST(TokenizeWord, TakeWordSimple0)
{
	t_char_iter itr;
	char		*input = "yilmaz";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("yilmaz");
	expected_token->type = WORD;
	
	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeWord, TakeWordSimple1)
{
	t_char_iter itr;
	char		*input = "yil maz";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("yil");
	expected_token->type = WORD;
	
	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizeWord, TakeWordSimple2)
{
	t_char_iter itr;
	char		*input = "ls|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("ls");
	expected_token->type = WORD;
	
	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizeWord, TakeWordSimple3)
{
	t_char_iter itr;
	char		*input = "#$^|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("#$^");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizeWord, TakeWordHard0)
{
	t_char_iter itr;
	char		*input = "a|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("a");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizeWord, TakeWordWithDoubleQuotes)
{
	t_char_iter itr;
	char		*input = "l\"s -la\"|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\"s -la\"");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizeWord, TakeWordWithSingleQuotes)
{
	t_char_iter itr;
	char		*input = "l\'s -la\'|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\'s -la\'");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizeWord, TakeWordWithUnclosedDoubleQuotes)
{
	t_char_iter itr;
	char		*input = "l\"s -la|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\"s -la|grep codam");
	expected_token->type = ERROR;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeWord, TakeWordWithUnclosedSingleQuotes)
{
	t_char_iter itr;
	char		*input = "l\'s -la|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\'s -la|grep codam");
	expected_token->type = ERROR;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeWord, TakeWordWithFourDoubleQuotes)
{
	t_char_iter itr;
	char		*input = "l\"s -la\"\"HOME\";grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\"s -la\"\"HOME\"");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(';', *itr);
}

TEST(TokenizeWord, TakeWordWithOpeningDoubleQuoteAndClosingSingleQuote)
{
	t_char_iter itr;
	char		*input = "l\"s -la\'|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\"s -la\'|grep codam");
	expected_token->type = ERROR;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeWord, TakeWordWithOpeningSingleQuoteAndClosingDoubleQuote)
{
	t_char_iter itr;
	char		*input = "l\'s -la\"|grep codam";

	itr = input;
	actual_token = take_word(&itr, env_list, 0);
	expected_token->content = ft_strdup("l\'s -la\"|grep codam");
	expected_token->type = ERROR;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}