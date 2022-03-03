/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expand_single_token.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 16:55:24 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/03/03 13:34:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/expander/expand_single_token.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/parser/create_parse_list.h"
#include "utils.h"

/* Variables */
static t_list	*expected_token_list;
static t_list	*actual_token_list;
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

TEST_GROUP(ExpandSingleToken);

TEST_SETUP(ExpandSingleToken)
{
	env_list = create_env_list(env);
	expected_token_list = NULL;
	actual_token_list = NULL;
}

TEST_TEAR_DOWN(ExpandSingleToken)
{
	ft_lstclear(&env_list, free_env_variable);
	ft_lstclear(&actual_token_list, free_token);
	ft_lstclear(&expected_token_list, free_token);
}

TEST(ExpandSingleToken, Simple0)
{
	char	*input = "cat -c $hilmi_8";

	/* Tokenize and expand */
	actual_token_list = tokenize_input(input);

	/* Get $hilmi_8 token */
	t_token	*token = actual_token_list->next->next->content;

	/* Expected token */
	expand_single_token(token, env_list);

	/* Actual token */
	
}