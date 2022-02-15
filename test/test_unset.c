/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_unset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/12 17:49:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/12 18:05:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Unity unit-tester */
#include "unity_fixture.h"

/* File to test */
#include "../incl/commands.h"

/* User defined headers */
#include "../incl/minishell.h"
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
static char		*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							NULL,
						};

TEST_GROUP(UnsetBuiltin);

TEST_SETUP(UnsetBuiltin)
{
	token_list = NULL;
	parse_list = NULL;
	env_list = add_envp(env);
}

TEST_TEAR_DOWN(UnsetBuiltin)
{
}

// delete from middle
// delete first
// delete last
// delete all
// delete non existing
// delete all and extra
// codam=hilmi --> unset codamm

TEST(UnsetBuiltin, DeleteFromMiddle)
{
	char	*input = "unset LOGNAME";

	/* Tokenize and parse */
	token_list = tokenize_input(input);
	parse_list = create_parse_list(token_list);

	/* Expected environment list */
	expected_env = copy_environment_linked_list(env_list);

	
}
