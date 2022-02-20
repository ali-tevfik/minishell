/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenize_word.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:38:39 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 11:31:33 by hyilmaz       ########   odam.nl         */
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
	actual_token = take_word(&itr);
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
	actual_token = take_word(&itr);
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
	actual_token = take_word(&itr);
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
	actual_token = take_word(&itr);
	expected_token->content = ft_strdup("a");
	expected_token->type = WORD;
	
	TEST_ASSERT_EQUAL_STRING(expected_token->content, actual_token->content);
	TEST_ASSERT_EQUAL_INT(expected_token->type, actual_token->type);

	/* Check that iter moved to next character */
	TEST_ASSERT_EQUAL_CHAR('|', *itr);
}