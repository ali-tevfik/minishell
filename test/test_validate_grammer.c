/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_validate_grammer.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:04:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/23 13:49:38 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** This script checks the correctness of the grammer of the input string (the command).
** Checks for the following:
** 1. There can be no PIPE after a PIPE.
** 2. There can be no PIPE or REDIRECTION after a REDIRECTION (has to be a WORD, the filename).
*/

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/validate_grammer.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer_utils.h"
#include "../src/tokenizer/tokenizer.h"

/* System headers */
#include <stdio.h>

/* Variables */
t_list	*actual_list;

TEST_GROUP(CheckGrammer);

TEST_SETUP(CheckGrammer)
{
}

TEST_TEAR_DOWN(CheckGrammer)
{
	ft_lstclear(&actual_list, free_token);
}

TEST(CheckGrammer, PipesBackToBack)
{
	char	*input = "ls || grep codam";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, RedirectionBeforePipe)
{
	char	*input = "grep codam > | ls -l";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, RedirectionAfterPipe)
{
	char	*input = "grep codam | > file_out ls -l";	/* Same as ls -l > file_out */
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}

TEST(CheckGrammer, RedirectionAfterRedirection)
{
	char	*input = "grep codam | > >> file_out ls -l";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, ErrorTokenAmpersandInList)
{
	char	*input = "grep codam & ls -l > file_out";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, ErrorTokenSemiColonInList)
{
	char	*input = "grep codam ; ls -l > file_out";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, OnlyPipeToken)
{
	char	*input = "|";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, OnlyRedirectionToken)
{
	char	*input = "   <   ";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, OnlyRedirectionToken1)
{
	char	*input = "   <<";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, NoClosingDQuote)
{
	char	*input = "echo \"$HOME";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, NoClosingQuote)
{
	char	*input = "echo \'$HOME";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, SingleDoubleSingleDoubleQuotesSequence)
{
	char	*input = "echo \'\"\'\"";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, DoubleSingleDoubleSingleQuotesSequence)
{
	char	*input = "echo \"\'\"\'";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, CorrectGrammer0)
{
	char	*input = "< infile ls -l > files | grep codam | wc -l > outfile";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}

TEST(CheckGrammer, CorrectGrammer1)
{
	char	*input = "ls > ls.out -la";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}

TEST(CheckGrammer, CorrectGrammer2)
{
	char	*input = "> ls.out ls -la";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}

TEST(CheckGrammer, EndWithRedirToken)
{
	char	*input = "echo a >";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, EndWithPipeToken)
{
	char	*input = "echo a |";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, StartWithSemicolonToken)
{
	char	*input = ";s";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, StartWithAmpersandToken)
{
	char	*input = "&s";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, OnlySemicolonToken)
{
	char	*input = ";";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, OnlyAmpersandToken)
{
	char	*input = "&";
	actual_list = tokenize_input(input, NULL, 0);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}