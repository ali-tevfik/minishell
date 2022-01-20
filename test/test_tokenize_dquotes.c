/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_dquotes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:09:05 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:30:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_dquotes.h"

/* System headers */
#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizeDquotes);

TEST_SETUP(TokenizeDquotes)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizeDquotes)
{
	free(expected_token);
	free(actual_token);
}

TEST(TokenizeDquotes, TakeDoubleQuotesSimple0)
{
	t_char_iter	itr;
	char		*input = "\"hilmi yilmaz\"check";

	itr = input;
	actual_token = take_double_quotes(&itr);
	expected_token->content = input;
	expected_token->len_content = 14;
	expected_token->type = DQUOTE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('c', *itr);
}

TEST(TokenizeDquotes, TakeDoubleQuotesSimple1)
{
	t_char_iter	itr;
	char		*input = "\"ls -l | grep codam &\"";

	itr = input;
	actual_token = take_double_quotes(&itr);
	expected_token->content = input;
	expected_token->len_content = 22;
	expected_token->type = DQUOTE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeDquotes, TakeDoubleQuotesNoClosingQuote)
{
	t_char_iter	itr;
	char		*input = "echo \"$HOME";

	itr = input + 5;
	actual_token = take_double_quotes(&itr);
	expected_token->content = input + 5;
	expected_token->len_content = 6;
	expected_token->type = ERROR;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}

TEST(TokenizeDquotes, TakeDoubleQuotesBackToBack)
{
	t_char_iter	itr;
	char		*input = "echo \"\"ha";

	itr = input + 5;
	actual_token = take_double_quotes(&itr);
	expected_token->content = input + 5;
	expected_token->len_content = 2;
	expected_token->type = DQUOTE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('h', *itr);
}

// TEST(TokenizeDquotes, TakeDoubleQuotesNestedHard0)
// {
// 	t_char_iter	itr;
// 	char		*input = "echo \"my homefolder is -->\"$HOME\"<--\"";

// 	itr = input + 5;
// 	actual_token = take_double_quotes(&itr);
// 	expected_token->content = input + 5;
// 	expected_token->len_content = 32;
// 	expected_token->type = DQUOTE;

// 	/* Compare structs */
// 	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

// 	/* Check that iter moved to next character */
// 	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
// }

// TEST(TokenizeDquotes, TakeDoubleQuotesNestedHard1)
// {
// 	t_char_iter	itr;
// 	char		*input = "echo \"my homefolder is -->\"$HOME\"<--\" | echo \"$PATH\"";

// 	itr = input + 5;
// 	actual_token = take_double_quotes(&itr);
// 	expected_token->content = input + 5;
// 	expected_token->len_content = 32;
// 	expected_token->type = DQUOTE;

// 	/* Compare structs */
// 	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

// 	/* Check that iter moved to next character */
// 	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
// }