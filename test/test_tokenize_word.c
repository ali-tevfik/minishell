/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_word.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:38:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:30:54 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenize_word.h"

/* System headers */
#include <stdlib.h>

t_token		*actual_token;
t_token		*expected_token;

TEST_GROUP(TokenizeWord);

TEST_SETUP(TokenizeWord)
{
	actual_token = NULL;
	expected_token = calloc(1, sizeof(t_token));
}

TEST_TEAR_DOWN(TokenizeWord)
{
	free(expected_token);
	free(actual_token);
}

TEST(TokenizeWord, TakeWordSimple0)
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

TEST(TokenizeWord, TakeWordSimple1)
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

TEST(TokenizeWord, TakeWordSimple2)
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

TEST(TokenizeWord, TakeWordSimple3)
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