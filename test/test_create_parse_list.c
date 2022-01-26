/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_create_parse_list.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:58:27 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 18:45:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/parser/create_parse_list.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "utils.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

/* Variables */
t_list	*expected_pipeline;
t_list	*actual_pipeline;
t_list	*token_list;

TEST_GROUP(CreateParseList);

TEST_SETUP(CreateParseList)
{
}

TEST_TEAR_DOWN(CreateParseList)
{
}

TEST(CreateParseList, SimplePipelineNoPipes)
{
	TEST_IGNORE();
	char	*input = "ls -l";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected list */
	expected_pipeline->content = ft_calloc(1, sizeof(t_command));
	expected_pipeline->next = NULL;
	((t_command *)(expected_pipeline->content))->command[0] = ft_strdup("ls");
	((t_command *)(expected_pipeline->content))->command[1] = ft_strdup("-l");
	((t_command *)(expected_pipeline->content))->command[2] = NULL;
	((t_command *)(expected_pipeline->content))->in_file = NULL;
	((t_command *)(expected_pipeline->content))->out_file = NULL;
	((t_command *)(expected_pipeline->content))->redirection_operator_in = NONE;
	((t_command *)(expected_pipeline->content))->redirection_operator_out = NONE;	

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

//char	*input = "ls -l | grep codam > out_file | < in_file wc -l > out_file_2