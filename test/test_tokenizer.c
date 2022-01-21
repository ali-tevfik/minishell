/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenizer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/21 16:34:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenizer.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer_utils.h"

/* System headers */
#include <stdio.h>

/* Variables */
t_list		*expected_list;

TEST_GROUP(Tokenizer);

TEST_SETUP(Tokenizer)
{
}

TEST_TEAR_DOWN(Tokenizer)
{
}

TEST(Tokenizer, Command)
{
	char	*input = "ls";
	t_token	token;
	t_list	*actual_list = tokenize_input(input);

	token.content = input;
	token.len_content = 2;
	token.type = WORD;
	expected_list = ft_lstnew(&token);

	/* Compare the length of the linked lists. */
	int actual_len = ft_lstsize(actual_list);
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, actual_len, "Input: \"ls\"");

	/* Compare elements of the linked lists */
	TEST_ASSERT_EQUAL_MEMORY(expected_list->content, actual_list->content, sizeof(t_token));
}

TEST(Tokenizer, CommandPlusArgument)
{
	char	*input = "ls -l";
	t_token	*token;
	t_list	*actual_list = tokenize_input(input);

	token = create_token(input, 2, WORD);
	expected_list = ft_lstnew(token);

	token = create_token(input + 3, 2, WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare the length of the linked lists. */
	int actual_len = ft_lstsize(actual_list);
	TEST_ASSERT_EQUAL_INT_MESSAGE(2, actual_len, "Input: \"ls\"");

	/* Compare elements of the linked lists */
	TEST_ASSERT_EQUAL_MEMORY(expected_list->content, actual_list->content, sizeof(t_token));
	TEST_ASSERT_EQUAL_MEMORY(expected_list->next->content, actual_list->next->content, sizeof(t_token));
}

TEST(Tokenizer, MultipleCommandsPlusArgumentsWithPipes)
{
	char	*input = "ls -l | grep codam | wc -l";
	t_token	*token;
	t_list	*actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(input, 2, WORD);					/* ls */
	expected_list = ft_lstnew(token);

	token = create_token(input + 3, 2, WORD);				/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 6, 1, PIPE);				/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 8, 4, WORD);				/* grep */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 13, 5, WORD);				/* codam */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 19, 1, PIPE);				/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 21, 2, WORD);				/* wc */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 24, 2, WORD);				/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare the length of the linked lists. */
	int actual_len = ft_lstsize(actual_list);
	TEST_ASSERT_EQUAL_INT_MESSAGE(8, actual_len, "Input: \"ls -l | grep codam | wc -l\"");

	/* Compare elements of the linked lists */
	int	i = 0;
	t_list	*expected_head = expected_list;
	t_list	*actual_head = actual_list;
	while (i < 8)
	{
		TEST_ASSERT_EQUAL_MEMORY(expected_head->content, actual_head->content, sizeof(t_token));
		expected_head = expected_head->next;
		actual_head = actual_head->next;
		i++;
	}
}

TEST(Tokenizer, CommandPlusRedirection)
{
	char	*input = "< input_file hahah";
	t_token	*token;
	t_list	*actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(input, 1, REDIRECTION);
	expected_list = ft_lstnew(token);

	token = create_token(input + 2, 10, WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 13, 5, WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare the length of the linked lists. */
	int actual_len = ft_lstsize(actual_list);
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, actual_len, "Input: \"< input_file hahah\"");

	/* Compare elements of the linked lists */
	t_list	*expected_head = expected_list;
	t_list	*actual_head = actual_list;
	while (1)
	{
		TEST_ASSERT_EQUAL_MEMORY(expected_head->content, actual_head->content, sizeof(t_token));
		if (expected_head->next == NULL)
			break ;
		expected_head = expected_head->next;
		actual_head = actual_head->next;
	}
}

TEST(Tokenizer, CommandPlusRedirectionPlusPipes)
{
	char	*input = "< ls -l -a ~/Desktop | wc -l > outfile";
	t_token	*token;
	t_list	*actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(input, 1, REDIRECTION);		/* < */
	expected_list = ft_lstnew(token);

	token = create_token(input + 2, 2, WORD);			/* ls */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 5, 2, WORD);			/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 8, 2, WORD);			/* -a */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 11, 9, WORD);			/* ~/Desktop */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 21, 1, PIPE);			/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 23, 2, WORD);			/* wc */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 26, 2, WORD);			/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 29, 1, REDIRECTION);	/* > */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(input + 31, 7, WORD);			/* outfile */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare the length of the linked lists. */
	int actual_len = ft_lstsize(actual_list);
	TEST_ASSERT_EQUAL_INT_MESSAGE(10, actual_len, "Input: \"< ls -l -a ~/Desktop | wc -l > outfile\"");

	/* Compare elements of the linked lists */
	t_list	*expected_head = expected_list;
	t_list	*actual_head = actual_list;
	while (1)
	{
		TEST_ASSERT_EQUAL_MEMORY(expected_head->content, actual_head->content, sizeof(t_token));
		if (expected_head->next == NULL)
			break ;
		expected_head = expected_head->next;
		actual_head = actual_head->next;
	}
}
