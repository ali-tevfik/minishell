/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 12:13:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 14:14:12 by hyilmaz       ########   odam.nl         */
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
** Append slashes to end of PATH's.
*/

static bool	append_slash_suffix_to_path(char **path)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (path[i] == NULL)
		{
			perror("Error with malloc");
			return (false);
		}
		free(tmp);
		i++;
	}
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
** Returns false when malloc fails, true otherwise.
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
** 
** Returns:
** 		false if malloc failed. Minishell should stop.
**		true otherwise
*/

/* USE OWN GETENV */
bool	find_command(t_command *command)
{
	char	*path;
	char	**path_array;

	path = getenv("PATH");
	if (path == NULL)
		return (true);
	path_array = ft_split(path, ':');
	if (path_array == NULL)
	{
		perror("Error with malloc");
		return (false);
	}
	if (check_given_executable_on_slashes(command->command[0]))
		return (true);
	if (!append_slash_suffix_to_path(path_array))
		return (false);
	 return (get_executable_with_full_path(path_array, &command->command[0]));
}
