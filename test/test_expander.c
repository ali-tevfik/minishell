/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expander.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 15:42:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/15 15:58:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../src/expander/expander.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/tokenizer/tokenizer_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/parser/create_parse_list.h"
#include "utils.h"

/* Variables */
static t_list	*token_list;
static t_list	*parse_list;
static t_list	*env_list;
static t_list	*expected_env;
static t_list	*actual_env;
static t_env	*env_variable;
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							NULL,
						};

TEST_GROUP(Expander);

TEST_SETUP(Expander)
{
}

TEST_TEAR_DOWN(Expander)
{
}

TEST(Expander, ExpandSimple0)
{
	char	*input = "echo $PATH";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	
}
