/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:51:38 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/24 17:58:46 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/parser/parser.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

TEST_GROUP(Parser);

TEST_SETUP(Parser)
{
}

TEST_TEAR_DOWN(Parser)
{
}

TEST(Parser, CreateParseTree)
{
	char	*input = "ls -l | wc -l > out_file";
	
	/* Expected parse tree */

	/* ROOT */
	t_pipeline *tree_root = ft_calloc(1, sizeof(t_pipeline));
	tree_root->command = ft_calloc(1, sizeof(t_command));
	tree_root->command->command = ft_strdup("ls -l");
	tree_root->command->filename = NULL;
	tree_root->command->redirection_operator = NULL;

	/* LEFT CHILD */
	tree_root->pipeline = ft_calloc(1, sizeof(t_pipeline));
	tree_root->pipeline->command = ft_calloc(1, sizeof(t_command));
	tree_root->pipeline->command->command = ft_strdup("wc -l");
	tree_root->pipeline->command->filename = ft_strdup("out_file");
	tree_root->pipeline->command->redirection_operator = ft_strdup(">");

	

}
