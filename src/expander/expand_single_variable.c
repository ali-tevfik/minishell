/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_single_variable.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 18:57:57 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/18 15:31:59 by hyilmaz       ########   odam.nl         */
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
** Loop only n characters.
** Returns NULL when allocation fails.
** Returns "" (empty string) if key not found in environment.
*/

char	*expand_single_variable(t_list *env_list, char *string, size_t n)
{
	size_t	i;
	char	*key;
	char	*value;
	char	*remainder;
	char	*expansion;

	i = 1;
	value = NULL;
	if (is_separator(string[i]))
	{
		expansion = ft_substr(string, 0, n);
		return (expansion);
	}
	while (string[i] != '\0' && i < n)
	{
		if (is_separator(string[i]))
			break ;
		i++;
	}
	key = ft_substr(string, 1, i - 1);
	if (key == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	remainder = ft_substr(string, i, n);
	if (remainder == NULL)
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
	expansion = ft_strjoin(value, remainder);
	if (expansion == NULL)
	{
		perror("Error with malloc");
		return (NULL);
	}
	free(value);
	free(remainder);
	return (expansion);
}