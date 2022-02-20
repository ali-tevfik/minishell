/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenizer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/20 12:56:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/tokenizer/tokenizer.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer_utils.h"
#include "utils.h"

/* System headers */
#include <stdio.h>

/* Variables */
t_list		*actual_list;
t_list		*expected_list;

TEST_GROUP(Tokenizer);

TEST_SETUP(Tokenizer)
{
}

TEST_TEAR_DOWN(Tokenizer)
{
	ft_lstclear(&actual_list, free_token);
	ft_lstclear(&expected_list, free_token);
}

TEST(Tokenizer, Command)
{
	char	*input = "ls";
	t_token	*token;
	actual_list = tokenize_input(input);

	token = create_token(ft_strdup("ls"), WORD);
	expected_list = ft_lstnew(token);

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusArgument)
{
	char	*input = "ls -l";
	t_token	*token;
	actual_list = tokenize_input(input);

	token = create_token(ft_strdup("ls"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("-l"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusArgumentStartingWithSomeSpaces)
{
	char	*input = "   ls -l";
	t_token	*token;
	actual_list = tokenize_input(input);

	token = create_token(ft_strdup("ls"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("-l"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, MultipleCommandsPlusArgumentsWithPipes)
{
	char	*input = "ls -l | grep codam | wc -l";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("ls"), WORD);				/* ls */
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("-l"), WORD);				/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);							/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("grep"), WORD);				/* grep */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);				/* codam */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);							/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("wc"), WORD);				/* wc */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("-l"), WORD);				/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusRedirection)
{
	char	*input = "< input_file hahah";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(NULL, READ);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("input_file"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("hahah"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusRedirectionPlusPipes)
{
	char	*input = "< ls -l -a ~/Desktop | wc -l > outfile";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(NULL, READ);						/* < */
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("ls"), WORD);			/* ls */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("-l"), WORD);			/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("-a"), WORD);			/* -a */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("~/Desktop"), WORD);		/* ~/Desktop */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);						/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("wc"), WORD);			/* wc */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("-l"), WORD);			/* -l */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, WRITE);						/* > */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("outfile"), WORD);		/* outfile */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusDquotes)
{
	char	*input = "echo \"$HOME\"";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("$HOME"), DQUOTE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list); 
}

TEST(Tokenizer, CommandPlusDquotesEmpty)
{
	char	*input = "echo \"\"";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup(""), DQUOTE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusDquotesPlusPipes)
{
	char	*input = "echo \"$HOME\" | grep \"codam amsterdam\"";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("$HOME"), DQUOTE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("grep"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam amsterdam"), DQUOTE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusQuotes)
{
	char	*input = "echo \'$HOME\'";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("$HOME"), QUOTE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusUnclosedQuotes)
{
	char	*input = "echo \'hilmi | wc -l";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("hilmi | wc -l"), ERROR);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, MultiplePipesBackToBack)
{
	char	*input = "|| |||";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(NULL, PIPE);
	expected_list = ft_lstnew(token);

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, WeirdSpacing)
{
	char	*input = "\techo   hilmi|grep   \t codam";
	t_token	*token;
	actual_list = tokenize_input(input);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);			/* echo */
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("hilmi"), WORD);			/* hilmi */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);						/* | */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("grep"), WORD);			/* grep */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("codam"), WORD);			/* codam */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}