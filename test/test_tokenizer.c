/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tokenizer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 13:41:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/18 17:12:45 by hyilmaz       ########   odam.nl         */
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

/* User defined headers */
#include "utils.h"

/* Variables */
t_list		*actual_list;
t_list		*expected_list;
static t_list	*env_list;
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"HOME=/home/hilmi",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							"a=b",
							"hilmi_8=bro",
							"codam_=",
							"test=hilmi yilmaz",
							"hilmi=ho -n",
							NULL,
						};

TEST_GROUP(Tokenizer);

TEST_SETUP(Tokenizer)
{
	env_list = create_env_list(env);
}

TEST_TEAR_DOWN(Tokenizer)
{
	ft_lstclear(&env_list, free_env_variable);
	ft_lstclear(&actual_list, free_token);
	ft_lstclear(&expected_list, free_token);
}

TEST(Tokenizer, Command)
{
	char	*input = "ls";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	token = create_token(ft_strdup("ls"), WORD);
	expected_list = ft_lstnew(token);

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusArgument)
{
	char	*input = "ls -l";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

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
	actual_list = tokenize_input(input, env_list, 0);

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
	actual_list = tokenize_input(input, env_list, 0);

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
	actual_list = tokenize_input(input, env_list, 0);

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
	actual_list = tokenize_input(input, env_list, 0);

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
	char	*input = "echo \"HOME\"";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("\"HOME\""), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusDquotesEmpty)
{
	char	*input = "echo \"\"";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("\"\""), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusDquotesPlusPipes)
{
	char	*input = "echo \"HOME\" | grep \"codam amsterdam\"";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("\"HOME\""), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, PIPE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("grep"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(ft_strdup("\"codam amsterdam\""), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusQuotes)
{
	char	*input = "echo \'HOME\'";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("\'HOME\'"), WORD);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, CommandPlusUnclosedQuotes)
{
	char	*input = "echo \'hilmi | wc -l";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("\'hilmi | wc -l"), ERROR);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}

TEST(Tokenizer, MultiplePipesBackToBack)
{
	char	*input = "|| |||";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

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
	actual_list = tokenize_input(input, env_list, 0);

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

TEST(Tokenizer, hallo)
{
	char	*input = "echo a > ";
	t_token	*token;
	actual_list = tokenize_input(input, env_list, 0);

	/* Create the expected token */
	token = create_token(ft_strdup("echo"), WORD);			/* echo */
	expected_list = ft_lstnew(token);

	token = create_token(ft_strdup("a"), WORD);				/* hilmi */
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	token = create_token(NULL, WRITE);
	ft_lstadd_back(&expected_list, ft_lstnew(token));

	/* Compare token lists */
	compare_token_lists(expected_list, actual_list);
}
