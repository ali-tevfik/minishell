/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_quotes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:37:04 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 11:47:58 by hyilmaz       ########   odam.nl         */
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
	free(expected_token);
	free(actual_token);
}

TEST(TokenizeQuotes, TakeSingleQuotesSimple0)
{
	t_char_iter	itr;
	char		*input = "\'hilmi\'codam";

	itr = input;
	actual_token = take_single_quotes(&itr);
	expected_token->content = input;
	expected_token->len_content = 7;
	expected_token->type = QUOTE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('c', *itr);
}

TEST(TokenizeQuotes, TakeSingleQuotesSimple1)
{
	t_char_iter	itr;
	char		*input = "\'ls -l | grep codam &\'";

	itr = input;
	actual_token = take_single_quotes(&itr);
	expected_token->content = input;
	expected_token->len_content = 22;
	expected_token->type = QUOTE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('\0', *itr);
}