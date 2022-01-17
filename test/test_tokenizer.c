/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenizer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/17 18:05:24 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../src/libft/libft.h"
#include "../src/parser/tokenizer.h"

#include <stdio.h>

/* Create a token struct out of the arguments */
static t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->content = content;
	token->type = type;
	return (token);
}

TEST_GROUP(Tokenizer);

TEST_SETUP(Tokenizer)
{
}

TEST_TEAR_DOWN(Tokenizer)
{
}

TEST(Tokenizer, SimpleInput)
{
	char	*input_string = "ls";

	/* One token */
	t_token	*token = create_token(input_string, WORD);

	t_list	*expected = ft_lstnew(token);				/* The result that is expected */
	t_list	*actual = tokenize_input(input_string);		/* My result */

	/* Compare the length of the linked lists. */
	int expected_len = 1;
	int actual_len = ft_lstsize(actual);
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected_len, actual_len, "Input: \"ls\"");

	/* Compare elements of the linked lists */
	TEST_ASSERT_EQUAL_MEMORY(expected->content, actual->content, sizeof(t_token));
}

// TEST(Tokenizer, SimpleInput)
// {
// 	char	*input_string = "ls";

// 	t_list	*expected = ft_lstnew("ls");				/* The result that is expected */
// 	t_list	*actual = tokenize_input(input_string);		/* My result */

// 	/* Compare the length of the linked lists. */
// 	int expected_len = 1;
// 	int actual_len = ft_lstsize(actual);
// 	TEST_ASSERT_EQUAL_INT_MESSAGE(expected_len, actual_len, "Input: \"ls\"");

// 	/* Compare elements of the linked lists */
// 	TEST_ASSERT_EQUAL_STRING_MESSAGE((char *)expected->content, (char *)actual->content, "Input: \"ls\"");
// }

TEST(Tokenizer, CommandPlusArgument)
{
	char	*input_string = "ls -l";

	t_list	*expected = ft_lstnew("ls");				/* The result that is expected */
	ft_lstadd_back(&expected, ft_lstnew("-l"));
	t_list	*actual = tokenize_input(input_string);		/* My result */

	/* Compare the length of the linked lists. */
	int expected_len = 2;
	int actual_len = ft_lstsize(actual);
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected_len, actual_len, "Input: \"ls -l\"");

	/* Compare elements of the linked lists */
	TEST_ASSERT_EQUAL_STRING_MESSAGE((char *)expected->content, (char *)actual->content, "Input: \"ls -l\"");
}