/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_find_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:27:18 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/15 14:33:59 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/executor/find_command.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/create_parse_list.h"
#include "../src/parser/parser_data_structs.h"
#include "../incl/built_in.h"
#include "utils.h"

/* System headers */
#include <stdbool.h>
#include <stdlib.h>
#include <sys/utsname.h>

/* Variables */
char			**command_array;
char			*actual_command;
char			*expected_command;
struct utsname	uname_data;				/* To get operating system, Linux or Darwin */
static char			*env[] = {	"SHELL=/bin/zsh",
							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
							"LOGNAME=hyilmaz",
							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
							NULL,
						};
t_list	*env_list;

TEST_GROUP(FindCommand);

TEST_SETUP(FindCommand)
{
	uname(&uname_data);
	command_array = NULL;
	env_list = add_envp(env);
}

TEST_TEAR_DOWN(FindCommand)
{
	free(actual_command);
	free(expected_command);
	free_command(command_array);
}

TEST(FindCommand, CommandExistsWithoutPathLs)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "ls", "-l");
	else
		command_array = create_command(2, "ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/ls");
	else
		expected_command = ft_strdup("/bin/ls");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandExistsWithoutPathGrep)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "grep", "-l");
	else
		command_array = create_command(2, "grep", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/grep");
	else
		expected_command = ft_strdup("/usr/bin/grep");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}


TEST(FindCommand, CommandExistsWithRelativePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "../../../../usr/bin/ls", "-l");
	else
		command_array = create_command(2, "../../../../../bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("../../../../usr/bin/ls");
	else
		expected_command = ft_strdup("../../../../../bin/ls");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExistsWithRelativePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "../../usr/bin/ls", "-l");
	else
		command_array = create_command(2, "../../bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("../../usr/bin/ls");
	else
		expected_command = ft_strdup("../../bin/ls");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandExistsWithAbsolutePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "/usr/bin/ls", "-l");
	else
		command_array = create_command(2, "/bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/ls");
	else
		expected_command = ft_strdup("/bin/ls");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExistsWithAbsolutePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "/usr/sbin/hilmi/ls", "-l");
	else
		command_array = create_command(2, "/bin/hilmi/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/sbin/hilmi/ls");
	else
		expected_command = ft_strdup("/bin/hilmi/ls");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExist)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_array = create_command(2, "hilmi", "-l");
	else
		command_array = create_command(2, "hilmi", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("hilmi");
	else
		expected_command = ft_strdup("hilmi");

	/* Actual command */
	find_command(command_array, env_list);
	actual_command = ft_strdup(command_array[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

// TEST(FindCommand, NoPathAvailable)
// {
// 	/* Create command data struct */
// 	if (!ft_strncmp("Linux", uname_data.sysname, 5))
// 		command_array = create_command(2, "ls", "-l");
// 	else
// 		command_array = create_command(2, "ls", "-l");

// 	/* Expected command */
// 	if (!ft_strncmp("Linux", uname_data.sysname, 5))
// 		expected_command = ft_strdup("ls");
// 	else
// 		expected_command = ft_strdup("ls");

// 	/* Save and unset PATH variable */
// 	char *path = expander("PATH", env_list);
// 	unset_command(&env_list, "unset PATH");

// 	/* Actual command */
// 	find_command(command_array, env_list);
// 	actual_command = ft_strdup(command_array[0]);

// 	/* Compare commands */
// 	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);

// 	/* Reset PATH */
// 	export_command(&env_list, path);
// }
