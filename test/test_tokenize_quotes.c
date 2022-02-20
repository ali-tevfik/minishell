/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_quotes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:37:04 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 12:57:02 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_quotes.h"

/* System headers */
#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizeQuotes);

TEST_SETUP(TokenizeQuotes)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizeQuotes)
{
	free(expected_token->content);
	free(actual_token->content);
	free(expected_token);
	free(actual_token);
}

TEST(TokenizeQuotes, TakeSingleQuotesSimple0)
{
	t_char_iter	itr;
	char		*input = "\'hilmi\'codam";

	itr = input;
	actual_token = take_quotes(&itr, '\'');
	expected_token->content = ft_strdup("hilmi");
	expected_token->type = QUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('c', *itr);
}

TEST(TokenizeQuotes, TakeSingleQuotesSimple1)
{
	t_char_iter	itr;
	char		*input = "\'ls -l | grep codam &\'";

	itr = input;
	actual_token = take_quotes(&itr, '\'');
	expected_token->content = ft_strdup("ls -l | grep codam &");
	expected_token->type = QUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, TakeSingleQuotesHard0)
{
	t_char_iter	itr;
	char		*input = "\'\'";

	itr = input;
	actual_token = take_quotes(&itr, '\'');
	expected_token->content = ft_strdup("");
	expected_token->type = QUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, TakeSingleQuotesHard1)
{
	t_char_iter	itr;
	char		*input = "\'a\'";

	itr = input;
	actual_token = take_quotes(&itr, '\'');
	expected_token->content = ft_strdup("a");
	expected_token->type = QUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, TakeDoubleQuotesSimple0)
{
	t_char_iter	itr;
	char		*input = "\"hilmi\"codam";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("hilmi");
	expected_token->type = DQUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('c', *itr);
}

TEST(TokenizeQuotes, TakeDoubleQuotesSimple1)
{
	t_char_iter	itr;
	char		*input = "\"ls -l | grep codam &\"";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("ls -l | grep codam &");
	expected_token->type = DQUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, TakeDoubleQuotesHard0)
{
	t_char_iter	itr;
	char		*input = "\"\"";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("");
	expected_token->type = DQUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, TakeDoubleQuotesHard1)
{
	t_char_iter	itr;
	char		*input = "\"a\"";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("a");
	expected_token->type = DQUOTE;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, NoClosingSingleQuote)
{
	t_char_iter	itr;
	char		*input = "\'hilmi";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("hilmi");
	expected_token->type = ERROR;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeQuotes, NoClosingDoubleQuote)
{
	t_char_iter	itr;
	char		*input = "\"hilmi";

	itr = input;
	actual_token = take_quotes(&itr, '\"');
	expected_token->content = ft_strdup("hilmi");
	expected_token->type = ERROR;

	/* Compare tokens */
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}