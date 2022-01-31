/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_create_parse_list.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:58:27 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/31 17:26:15 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/parser/create_parse_list.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/tokenizer/tokenizer_utils.h"
#include "utils.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

/* Variables */
t_command	*command;
t_list		*expected_pipeline;
t_list		*actual_pipeline;
t_list		*token_list;

TEST_GROUP(CreateParseList);

TEST_SETUP(CreateParseList)
{
	expected_pipeline = NULL;
}

TEST_TEAR_DOWN(CreateParseList)
{
	ft_lstclear(&expected_pipeline, free_command);
	ft_lstclear(&actual_pipeline, free_command);
	ft_lstclear(&token_list, free_token);
}

TEST(CreateParseList, SimplePipelineNoPipes)
{
	char	*input = "ls -l";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	command = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	/* Actual list */
	actual_pipeline = create_parse_list(token_list);

	/* Compare lists length */
	int actual_len = ft_lstsize(actual_pipeline);
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, actual_len, "Input: \"ls -l\"");

	/* Compare all elements in the linked list */
	while (actual_pipeline != NULL)
	{
		compare_command_structs(expected_pipeline->content, actual_pipeline->content);
		actual_pipeline = actual_pipeline->next;
		expected_pipeline = expected_pipeline->next;
	}
}

TEST(CreateParseList, SimplePipelineOnePipe)
{
	char	*input = "ls -l | grep codam > out_file";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	command = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));
	
	command = create_command(NONE, OUT, NULL, ft_strdup("out_file"), 2, "grep", "codam");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	/* Actual list */
	actual_pipeline = create_parse_list(token_list);

	/* Compare lists length */
	int actual_len = ft_lstsize(actual_pipeline);
	TEST_ASSERT_EQUAL_INT_MESSAGE(2, actual_len, "Input: \"ls -l | grep codam > out_file\"");

	/* Compare all elements in the linked list */
	while (actual_pipeline != NULL)
	{
		compare_command_structs(expected_pipeline->content, actual_pipeline->content);
		actual_pipeline = actual_pipeline->next;
		expected_pipeline = expected_pipeline->next;
	}
}

TEST(CreateParseList, SimplePipelineTwoPipes)
{
	char	*input = "ls -l | grep codam > out_file | < in_file wc -l > out_file_2";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	command = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	command = create_command(NONE, OUT, NULL, ft_strdup("out_file"), 2, "grep", "codam");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	command = create_command(READ, OUT, ft_strdup("in_file"), ft_strdup("out_file_2"), 2, "wc", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	/* Actual list */
	actual_pipeline = create_parse_list(token_list);

	/* Compare lists length */
	int actual_len = ft_lstsize(actual_pipeline);
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, actual_len, "Input: \"ls -l | grep codam > out_file | < in_file wc -l > out_file_2\"");

	/* Compare all elements in the linked list */
	while (actual_pipeline != NULL)
	{
		compare_command_structs(expected_pipeline->content, actual_pipeline->content);
		actual_pipeline = actual_pipeline->next;
		expected_pipeline = expected_pipeline->next;
	}
}

TEST(CreateParseList, SimplePipelineTwoPipesChangeOrderCommandAndRedirection)
{
	char	*input = "ls -l | > out_file grep codam | < in_file wc > out_file_2 -l";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	command = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	command = create_command(NONE, OUT, NULL, ft_strdup("out_file"), 2, "grep", "codam");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	command = create_command(READ, OUT, ft_strdup("in_file"), ft_strdup("out_file_2"), 2, "wc", "-l");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	/* Actual list */
	actual_pipeline = create_parse_list(token_list);

	/* Compare lists length */
	int actual_len = ft_lstsize(actual_pipeline);
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, actual_len, "Input: \"ls -l | grep codam > out_file | < in_file wc -l > out_file_2\"");

	/* Compare all elements in the linked list */
	while (actual_pipeline != NULL)
	{
		compare_command_structs(expected_pipeline->content, actual_pipeline->content);
		actual_pipeline = actual_pipeline->next;
		expected_pipeline = expected_pipeline->next;
	}
}

TEST(CreateParseList, SimplePipelineNoPipeWeirdRedirectionOrder)
{
	char	*input = "grep < infile codam >> outfile -i";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	command = create_command(READ, APPEND, ft_strdup("infile"), ft_strdup("outfile"), 3, "grep", "codam", "-i");
	ft_lstadd_back(&expected_pipeline, ft_lstnew(command));

	/* Actual list */
	actual_pipeline = create_parse_list(token_list);

	/* Compare lists length */
	int actual_len = ft_lstsize(actual_pipeline);
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, actual_len, "Input: \"grep < infile codam >> outfile -i\"");

	/* Compare all elements in the linked list */
	while (actual_pipeline != NULL)
	{
		compare_command_structs(expected_pipeline->content, actual_pipeline->content);
		actual_pipeline = actual_pipeline->next;
		expected_pipeline = expected_pipeline->next;
	}
}
