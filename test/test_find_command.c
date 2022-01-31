/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_find_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:27:18 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/31 15:44:51 by hyilmaz       ########   odam.nl         */
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
#include <sys/utsname.h>

/* Variables */
t_command		*command_data;
char			*actual_command;
char			*expected_command;
bool			actual_return;
bool			expected_return;
struct utsname	uname_data;				/* To get operating system, Linux or Darwin */

TEST_GROUP(FindCommand);

TEST_SETUP(FindCommand)
{
	uname(&uname_data);
	command_data = NULL;
}

TEST_TEAR_DOWN(FindCommand)
{
	free_command(command_data);
	free(expected_command);
}

TEST(FindCommand, CommandExistsWithoutPath)
{
	/* Actual command and return */
	command_data = create_command(NONE, NONE, NULL, NULL, 2, "lshi", "-l");
	printf("\n%s\n", command_data->command[0]);
	printf("\n%s\n", command_data->command[1]);
	printf("\n%s\n", command_data->command[2]);
	free(command_data->command[0]);	/* <<<<<<< ---------------- ERROR HERE */

	
	actual_return = find_command(command_data);
	actual_command = command_data->command[0];

	/* Expected command and return */
	expected_return = true;
	if (!ft_strncmp("Linux", uname_data.sysname, 5))
		expected_command = ft_strdup("/usr/bin/ls");
	else
		expected_command = ft_strdup("/usr/bin/ls");
	
	/* Compare return values */
	TEST_ASSERT(expected_return == actual_return);

	/* Compare commands */
	TEST_ASSERT_EQUAL_STRING(expected_command, actual_command);
}

TEST(FindCommand, CommandExistsWithRelativePath)
{
	TEST_IGNORE();
}

TEST(FindCommand, CommandExistsWithAbsolutePath)
{
	TEST_IGNORE();
}


TEST(FindCommand, CommandDoesntExist)
{
	TEST_IGNORE();
}

TEST(FindCommand, NoPathAvailable)
{
	TEST_IGNORE();
}