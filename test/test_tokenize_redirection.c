/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_redirection.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:48:03 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 11:33:43 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_redirection.h"

/* System headers */
#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizeRedirection);

TEST_SETUP(TokenizeRedirection)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizeRedirection)
{
	free(expected_token);
	free(actual_token);
}

TEST(TokenizeRedirection, TakeRedirRightOnce)
{
	t_char_iter	itr;
	char		*input = "> out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 1;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizeRedirection, TakeRedirRightTwice)
{
	t_char_iter	itr;
	char		*input = ">>out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('o', *itr);
}

/* 
 * NOTE: may remove this.
 * The grammer check could also catch this error.
 */
TEST(TokenizeRedirection, TakeRedirRightTriple)
{
	TEST_IGNORE();
	t_char_iter	itr;
	char		*input = ">>>out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = ERROR;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character. This is the error character (one to many '>') */
	TEST_ASSERT_EQUAL_CHAR('>', *itr);
}

TEST(TokenizeRedirection, TakeRedirLeftOnce)
{
	t_char_iter	itr;
	char		*input = "< out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 1;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizeRedirection, TakeRedirLeftTwice)
{
	t_char_iter	itr;
	char		*input = "<<out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('o', *itr);
}

TEST(TokenizeRedirection, TakeRedirLeftRight)
{
	t_char_iter	itr;
	char		*input = "<>out_file";

	itr = input;
	actual_token = take_redirection(&itr);
	expected_token->content = input;
	expected_token->len_content = 1;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('>', *itr);

	free(actual_token);
	actual_token = take_redirection(&itr);
	expected_token->content = input + 1;
	expected_token->len_content = 1;
	expected_token->type = REDIRECTION;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('o', *itr);
}
