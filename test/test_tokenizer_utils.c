/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenizer_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:53:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 18:05:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../src/parser/tokenizer_utils.h"

#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizerUtils);

TEST_SETUP(TokenizerUtils)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizerUtils)
{
	free(expected_token);
	free(actual_token);
}

TEST(TokenizerUtils, TakeWordSimple0)
{
	t_char_iter itr;
	char		*input = "yilmaz";

	itr = input;
	actual_token = take_word(&itr);
	expected_token->content = input;
	expected_token->len_content = 6;
	expected_token->type = WORD;
	
	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));
}

TEST(TokenizerUtils, TakeWordSimple1)
{
	t_char_iter itr;
	char		*input = "yil maz";

	itr = input;
	actual_token = take_word(&itr);
	expected_token->content = input;
	expected_token->len_content = 3;
	expected_token->type = WORD;
	
	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizerUtils, TakeWordSimple2)
{
	t_char_iter itr;
	char		*input = "ls|grep codam";

	itr = input;
	actual_token = take_word(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = WORD;
	
	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizerUtils, TakeWordSimple3)
{
	t_char_iter itr;
	char		*input = "#$^&|grep codam";

	itr = input;
	actual_token = take_word(&itr);
	expected_token->content = input;
	expected_token->len_content = 4;
	expected_token->type = WORD;
	
	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}

TEST(TokenizerUtils, TakePipeSimple)
{
	t_char_iter	itr;
	char		*input = "| hilmi";

	itr = input;
	actual_token = take_pipe(&itr);
	expected_token->content = input;
	expected_token->len_content = 1;
	expected_token->type = PIPE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizerUtils, TakeRedirRightOnce)
{
	t_char_iter	itr;
	char		*input = "> out_file";

	itr = input;
	actual_token = take_redir_right(&itr);
	expected_token->content = input;
	expected_token->len_content = 1;
	expected_token->type = REDIR_RIGHT_ONCE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);
}

TEST(TokenizerUtils, TakeRedirRightTwice)
{
	t_char_iter	itr;
	char		*input = ">>out_file";

	itr = input;
	actual_token = take_redir_right(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = REDIR_RIGHT_TWICE;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('o', *itr);
}

/* 
 * NOTE: may remove this.
 * The grammer check could also catch this error.
 */
TEST(TokenizerUtils, TakeRedirRightTriple)
{
	t_char_iter	itr;
	char		*input = ">>>out_file";

	itr = input;
	actual_token = take_redir_right(&itr);
	expected_token->content = input;
	expected_token->len_content = 2;
	expected_token->type = ERROR;

	/* Compare structs */
	TEST_ASSERT_EQUAL_MEMORY(expected_token, actual_token, sizeof(t_token));

	/* Check that iter moved to next character. This is the error character (one to many '>') */
	TEST_ASSERT_EQUAL_CHAR('>', *itr);
}