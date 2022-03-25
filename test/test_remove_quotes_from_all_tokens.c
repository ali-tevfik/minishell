/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_remove_quotes_from_all_tokens.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 10:23:19 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/25 13:47:38 by hyilmaz       ########   odam.nl         */
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
	actual_list = tokenize_input(input, NULL, 0);
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
	actual_list = tokenize_input(input, NULL, 0);
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
	actual_list = tokenize_input(input, NULL, 0);
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
	actual_list = tokenize_input(input, NULL, 0);
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
	actual_list = tokenize_input(input, NULL, 0);
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
	actual_list = tokenize_input(input, NULL, 0);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("echo codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(RemoveQuotesFromTokens, PipesAndRedirectionOperatorsPresent)
{
	// TEST_IGNORE();
	char	*input = "< infile grep codam | wc -l >> outfile";

	/* Actual token list */
	actual_list = tokenize_input(input, NULL, 0);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(NULL, READ);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("infile"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("grep"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("wc"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("-l"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, APPEND);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("outfile"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

/*
** The empty quote should not be removed.
*/
TEST(RemoveQuotesFromTokens, EmptyQuote)
{
	char	*input = "ls \"\"";

	/* Actual token list */
	actual_list = tokenize_input(input, NULL, 0);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("ls"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("\"\""), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

/*
** Only remove outer quotes (first and last one).
*/
TEST(RemoveQuotesFromTokens, NestedQuotes)
{
	char	*input = "ls \"\'hilmi\'\"";

	/* Actual token list */
	actual_list = tokenize_input(input, NULL, 0);
	remove_quotes_from_all_tokens(actual_list);

	/* Expected token list */
	token = create_token(ft_strdup("ls"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("\'hilmi\'"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}
