/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_single_variable.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 18:57:57 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/21 15:03:01 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expand_single_variable.h"

/*
** Is character c an expansion separator?
** If so -> returns true
** else -> returns false
*/

static bool	is_separator(char c)
{
	if (ft_isalnum(c))			/* if number or letter */
		return (false);
	else if (c == '_')			/* if underscore */
		return (false);
	return (true);
}

/*
** Find out if "string" is an environmental variable.
** If so, return it, otherwise return NULL.
*/

static bool	get_value_of_key(t_list *env_list, char **value, char *key)
{
	while (env_list != NULL)
	{
		if (!match_str(((t_env *)(env_list->content))->key, key))
		{
			if (((t_env *)(env_list->content))->value == NULL)
				*value = ft_strdup("");
			else
				*value = ft_strdup(((t_env *)(env_list->content))->value);
			if (*value == NULL)
			{
				perror("Error with malloc");
				return (false);
			}
			break ;
		}
		env_list = env_list->next;
	}
	return (true);
}

/*
** First char of string has to be a dollar sign.
** len_variable is set as the length of the variable including dollar sign.
** Returns NULL when allocation fails.
** Returns "" (empty string) if key not found in environment.
*/

char	*expand_single_variable(t_list *env_list, char *string, size_t *len_variable)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 1;
	value = NULL;
	*len_variable = 1;
	if (is_separator(string[i]))
	{
		value = ft_substr(string, 0, 1);
		return (value);
	}
	while (string[i] != '\0')
	{
		if (is_separator(string[i]))
			break ;
		i++;
	}
	*len_variable = i;
	key = ft_substr(string, 1, i - 1);
	if (key == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	if (!get_value_of_key(env_list, &value, key))
		return (NULL);
	free(key);
	if (value == NULL)
	{
		value = ft_strdup("");
		if (value == NULL)
		{
			perror("Error with malloc");
			return (NULL);
		}
	}
	return (value);
}