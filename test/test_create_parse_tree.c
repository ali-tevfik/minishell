/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_create_parse_tree.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:58:27 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/26 14:04:00 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/parser/create_parse_tree.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/tokenizer/tokenizer.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

TEST_GROUP(CreateParseTree);

TEST_SETUP(CreateParseTree)
{
}

TEST_TEAR_DOWN(CreateParseTree)
{
}

TEST(CreateParseTree, SimplePipeline)
{
	char	*input = "ls -l | grep codam > out_file | < in_file wc -l > out_file_2";

	/* Expected output */
	
}