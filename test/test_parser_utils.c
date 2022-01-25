/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:01:59 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/25 15:33:02 by hyilmaz       ########   odam.nl         */
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
size_t	len_string_array(char **string_array)
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
	TEST_IGNORE();
	char	*input = "ls -l | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator = NONE;
	expected_command->filename = NULL;

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
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator, actual_command->redirection_operator);
	TEST_ASSERT_EQUAL_STRING(expected_command->filename, actual_command->filename);
}

TEST(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFile)
{
	TEST_IGNORE();
	char	*input = "ls -l > out_file | grep codam";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->command[0] = ft_strdup("ls");
	expected_command->command[1] = ft_strdup("-l");
	expected_command->command[2] = NULL;
	expected_command->redirection_operator = OUT;
	expected_command->filename = ft_strdup("out_file");

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
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator, actual_command->redirection_operator);
	TEST_ASSERT_EQUAL_STRING(expected_command->filename, actual_command->filename);

}

TEST(ParserUtils, CreateCommandFromTokenListNoPipeNoRedirection)
{
	TEST_IGNORE();
	char	*input = "ls -l";

	/* Tokenize input */
	token_list = tokenize_input(input);

	/* Expected command from tokens */
	expected_command = ft_calloc(1, sizeof(t_command));
	expected_command->command = ft_calloc(3, sizeof(char *));
	expected_command->filename = NULL;
	expected_command->redirection_operator = NONE;

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
	TEST_ASSERT_EQUAL_INT(expected_command->redirection_operator, actual_command->redirection_operator);
	TEST_ASSERT_EQUAL_STRING(expected_command->filename, actual_command->filename);
}