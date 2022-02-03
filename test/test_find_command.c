/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_find_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:27:18 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/03 15:24:48 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/executor/find_command.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/create_parse_list.h"
#include "../src/parser/parser_data_structs.h"
#include "utils.h"

/* System headers */
#include <stdbool.h>
#include <stdlib.h>
#include <sys/utsname.h>

/* Variables */
t_command		*command_data;
char			*actual_command;
char			*expected_command;
struct utsname	uname_data;				/* To get operating system, Linux or Darwin */

TEST_GROUP(FindCommand);

TEST_SETUP(FindCommand)
{
	uname(&uname_data);
	command_data = NULL;
}

TEST_TEAR_DOWN(FindCommand)
{
	free(actual_command);
	free(expected_command);
	free_command(command_data);
}

TEST(FindCommand, CommandExistsWithoutPathLs)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/ls");
	else
		expected_command = ft_strdup("/bin/ls");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandExistsWithoutPathGrep)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "grep", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "grep", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/grep");
	else
		expected_command = ft_strdup("/usr/bin/grep");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}


TEST(FindCommand, CommandExistsWithRelativePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "../../../../usr/bin/ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "../../../../../bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("../../../../usr/bin/ls");
	else
		expected_command = ft_strdup("../../../../../bin/ls");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExistsWithRelativePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "../../usr/bin/ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "../../bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("../../usr/bin/ls");
	else
		expected_command = ft_strdup("../../bin/ls");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandExistsWithAbsolutePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "/usr/bin/ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "/bin/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/ls");
	else
		expected_command = ft_strdup("/bin/ls");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExistsWithAbsolutePath)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "/usr/sbin/hilmi/ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "/bin/hilmi/ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/sbin/hilmi/ls");
	else
		expected_command = ft_strdup("/bin/hilmi/ls");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandDoesntExist)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "hilmi", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "hilmi", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("hilmi");
	else
		expected_command = ft_strdup("hilmi");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);	
}

TEST(FindCommand, NoPathAvailable)
{
	/* Create command data struct */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");
	else
		command_data = create_command(NONE, NONE, NULL, NULL, 2, "ls", "-l");

	/* Expected command */
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("ls");
	else
		expected_command = ft_strdup("ls");

	/* Save and unset PATH variable */
	char *path = getenv("PATH");
	unsetenv("PATH");

	/* Actual command */
	find_command(command_data);
	actual_command = ft_strdup(command_data->command[0]);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);	

	/* Reset PATH */
	setenv("PATH", path, 0);
}