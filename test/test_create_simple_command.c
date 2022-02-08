/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_create_simple_command.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:01:59 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/08 11:47:32 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** A pipeline is a single command or a sequence of commands separated by pipes.
** Example pipelines:
** --> ls -l
** --> ls -l | wc -l
*/

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/parser/create_simple_command.h"

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
t_list			*token_list;
char			**expected_command;
t_list			*redirection_list;
t_pipeline		*actual_pipeline;
t_pipeline		*expected_pipeline;

TEST_GROUP(CreateSimpleCommand);

TEST_SETUP(CreateSimpleCommand)
{
}

TEST_TEAR_DOWN(CreateSimpleCommand)
{
	free_pipeline(expected_pipeline);
	free_pipeline(actual_pipeline);
	ft_lstclear(&token_list, free_token);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenList)
{
	char	*input = "ls -l | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t		location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 4th token (3th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(3, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListTakeCommandAfterPipe)
{
	char	*input = "ls -l | grep codam";

	/* Tokenize input */
	t_list	*head = token_list;
	token_list = tokenize_input(input);
	head = token_list->next->next->next;

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "grep", "codam");
	redirection_list = create_redirection_list(0);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 3;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(head, &location_token);

	/* Check token location, should be after codam , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFile)
{
	char	*input = "ls -l > out_file | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(2, "out_file", OUT);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListWithMultipleRedirectionOutFile)
{
	char	*input = "< in_file ls -l > out_file | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(4, "in_file", READ, "out_file", OUT);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 8th token (7th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(7, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFileBeforeCommand)
{
	char	*input = "> out_file ls -l | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(2, "out_file", OUT);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFileInTheMiddleOfCommand)
{
	char	*input = "ls > out_file -l -a | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(3, "ls", "-l", "-a");
	redirection_list = create_redirection_list(2, "out_file", OUT);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(6, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListWithAppendOutFileInTheMiddleOfCommand)
{
	char	*input = "ls >> append_file -l -a";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(3, "ls", "-l", "-a");
	redirection_list = create_redirection_list(2, "append_file", APPEND);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

TEST(CreateSimpleCommand, CreateCommandFromTokenListNoPipeNoRedirection)
{
	char	*input = "ls -l";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected pipeline from tokens */
	expected_command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	expected_pipeline = create_pipeline_element(expected_command, redirection_list);

	/* Actual pipeline from tokens */
	size_t	location_token = 0;
	actual_pipeline = create_simple_pipeline_up_until_pipe_token(token_list, &location_token);

	/* End of tokenlist will be reached, so location should be 2 */
	TEST_ASSERT_EQUAL_size_t(2, location_token);

	/* Compare both actual and expected structs with each other */
	compare_pipelines(expected_pipeline, actual_pipeline);
}

// TEST(CreateSimpleCommand, CreateCommandFromTokenListStderrRedirect)
// {
// 	TEST_IGNORE();
// 	//char	*input = "ls -l 2 > out_file | grep codam";
// }