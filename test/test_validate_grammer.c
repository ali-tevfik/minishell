/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_validate_grammer.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:04:28 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/22 21:58:34 by hyilmaz       ########   odam.nl         */
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
t_list		*expected_list;

TEST_GROUP(CheckGrammer);

TEST_SETUP(CheckGrammer)
{
}

TEST_TEAR_DOWN(CheckGrammer)
{
}

TEST(CheckGrammer, PipesBackToBack)
{
	char	*input = "ls || grep codam";
	t_list	*actual_list = tokenize_input(input);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, RedirectionBeforePipe)
{
	char	*input = "grep codam > | ls -l";
	t_list	*actual_list = tokenize_input(input);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_FALSE(result);
}

TEST(CheckGrammer, RedirectionAfterPipe)
{
	char	*input = "grep codam | > file_out ls -l";	/* Same as ls -l > file_out */
	t_list	*actual_list = tokenize_input(input);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}

TEST(CheckGrammer, CorrectGrammer)
{
	char	*input = "< infile ls -l > files | grep codam | wc -l > outfile";
	t_list	*actual_list = tokenize_input(input);

	bool	result = validate_grammer(actual_list);
	TEST_ASSERT_TRUE(result);
}