/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_remove_quotes_from_all_tokens.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 10:23:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/23 11:09:51 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/remove_quotes_from_all_tokens.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer_utils.h"
#include "utils.h"

/* System headers */
#include <stdio.h>

/* Variables */
static t_list	*actual_list;
static t_list	*expected_list;
static t_token	*token;

TEST_GROUP(RemoveQuotesFromTokens);

TEST_SETUP(RemoveQuotesFromTokens)
{
	expected_list = NULL;
}

TEST_TEAR_DOWN(RemoveQuotesFromTokens)
{
	ft_lstclear(&actual_list, free_token);
	ft_lstclear(&expected_list, free_token);
}

TEST(RemoveQuotesFromTokens, NoQuotes)
{
	char	*input = "echo codam amsterdam";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("amsterdam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, DoubleQuotesPresent)
{
	char	*input = "echo \"codam\" amsterdam";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("amsterdam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, SingleQuotesPresent)
{
	char	*input = "echo \'codam\' amsterdam";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("amsterdam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, MultipleMixedQuotesPresent)
{
	char	*input = "echo \'codam\' \'amster\'dam\"ut\"recht";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("amsterdamutrecht"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, WordAppendWithDoubleQuotes)
{
	char	*input = "ec\"ho codam\"";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, WordAppendWithSingleQuotes)
{
	char	*input = "ec\'ho codam\'";

	/* Actual token list */
	actual_list = tokenize_input(input);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}