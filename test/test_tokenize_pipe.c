/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_pipe.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:25:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:30:44 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_pipe.h"

/* System headers */
#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizePipe);

TEST_SETUP(TokenizePipe)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizePipe)
{
	free(expected_token);
	free(actual_token);
}

TEST(TokenizePipe, TakePipeSimple)
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