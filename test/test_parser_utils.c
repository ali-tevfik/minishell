/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:01:59 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 14:01:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/parser/parser_utils.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/tokenizer/tokenizer.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

/* Variables */
t_list		*token_list;
t_command	*actual_command;
t_command	*expected_command;

/* Helper function */
static size_t	len_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
		i++;
	return (i);
}

TEST_GROUP(ParserUtils);

TEST_SETUP(ParserUtils)
{
}

TEST_TEAR_DOWN(ParserUtils)
{
}

TEST(ParserUtils, CreateCommandFromTokenList)
{
	char	*input = "ls -l | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = NONE;
	expected_command->in_file = NULL;
	expected_command->out_file = NULL;

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 4th token (3th if starting from 0)*/
	TEST_ASSERT_EQUAL_size_t(3, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFile)
{
	char	*input = "ls -l > out_file | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = OUT;
	expected_command->in_file = NULL;
	expected_command->out_file =  ft_strdup("out_file");

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListWithMultipleRedirectionOutFile)
{
	char	*input = "< in_file ls -l > out_file | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator_in = READ;
	expected_command->redirection_operator_out = OUT;
	expected_command->in_file = ft_strdup("in_file");
	expected_command->out_file =  ft_strdup("out_file");

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(7, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFileBeforeCommand)
{
	char	*input = "> out_file ls -l | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = OUT;
	expected_command->in_file = NULL;
	expected_command->out_file =  ft_strdup("out_file");

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFileInTheMiddleOfCommand)
{
	char	*input = "ls > out_file -l -a | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(4, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = ft_strdup("-a");
	expected_command->command[3] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = OUT;
	expected_command->in_file = NULL;
	expected_command->out_file =  ft_strdup("out_file");

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(6, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListWithAppendOutFileInTheMiddleOfCommand)
{
	char	*input = "ls >> out_file -l -a";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(4, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = ft_strdup("-a");
	expected_command->command[3] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = APPEND;
	expected_command->in_file = NULL;
	expected_command->out_file =  ft_strdup("out_file");

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* Check token location, should be at grep , so 6th token (5th if starting from 0) */
	TEST_ASSERT_EQUAL_size_t(5, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}

TEST(ParserUtils, CreateCommandFromTokenListNoPipeNoRedirection)
{
	char	*input = "ls -l";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator_in = NONE;
	expected_command->redirection_operator_out = NONE;
	expected_command->in_file = NULL;
	expected_command->out_file = NULL;

	/* Actual command from tokens */
	size_t	location_token = 0;
	actual_command = create_simple_command_up_until_pipe_token(token_list, &location_token);

	/* End of tokenlist will be reached, so location should be 2 */
	TEST_ASSERT_EQUAL_size_t(2, location_token);

	/* Check length of both command arrays */
	size_t	actual_len = len_string_array(actual_command->command);
	size_t	expected_len = len_string_array(expected_command->command);
	TEST_ASSERT_EQUAL_size_t(expected_len, actual_len);

	/* Check 2D command array */
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_command->command, actual_command->command, expected_len);

	/* Check filename and redirection operator */
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_in, actual_command->redirection_operator_in);
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator_out, actual_command->redirection_operator_out);
	TEST_ASSERT_EQUAL_STRING(expected_command->in_file, actual_command->in_file);
	TEST_ASSERT_EQUAL_STRING(expected_command->out_file, actual_command->out_file);
}