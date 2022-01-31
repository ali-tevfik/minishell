/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:13:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/31 15:43:53 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "find_command.h"

/*
** Checks whether the current executable is given with a path.
*/

static bool	check_given_executable_on_slashes(char *command)
{
	if (command == NULL)
		return (false);
	if (ft_strchr(command, '/') != NULL)	/* if slash found */
		return (true);
	return (false);
}

/*
** Append slash in front of the command.
*/

static bool	append_slash_in_front_of_command(char **command)
{
	char	*tmp;

	tmp = *command;
	*command = ft_strjoin("/", *command);
	if (*command == NULL)
	{
		perror("Error with malloc");
		return (false);
	}
	free(tmp);
	return (true);
}

/*
** Helper function for get_executable_with_full_path.
** If the command is found through appending a path, this function executes
** and fills the command in *cmd.
*/

static bool	found_command(char *command_with_path, char **cmd, char *tmp)
{
	free(*cmd);
	*cmd = ft_strdup(command_with_path);
	if (*cmd == NULL)
	{
		perror("Error with malloc");
		return (false);
	}
	free(command_with_path);
	command_with_path = tmp;
	return (true);
}

/*
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
*/

static bool	get_executable_with_full_path(char **path_array, char **command)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (path_array[i] != NULL)
	{
		tmp = path_array[i];
		path_array[i] = ft_strjoin(path_array[i], *command);
		if (path_array[i] == NULL)
		{
			perror("Error with malloc");
			return (false);
		}
		if (access(path_array[i], X_OK) == 0)
		{
			if (!found_command(path_array[i], command, tmp))
				return (false);
			return (true);
		}
		path_array[i] = tmp;
		i++;
	}
	return (true);
}

/*
** Steps:
** 1. Check given executable on slashes. If slashes present, return true.
** 2. If no slashes, get PATH from environment.
** 3. Append a "/" in front of the command.
** 4. Loop over PATH and try to find executable.
*/

bool	find_command(t_command *command)
{
	char	*path;
	char	**path_array;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("Error: no PATH in environment\n");
		return (false);
	}
	path_array = ft_split(path, ':');
	if (path_array == NULL)
	{
		printf("Error: no PATH in environment\n");
		return (false);
	}
	if (check_given_executable_on_slashes(command->command[0]))
		return (true);
	if (!append_slash_in_front_of_command(&command->command[0]))
		return (false);
	if (!get_executable_with_full_path(path_array, &command->command[0]))
		return (false);
	return (true);
}
