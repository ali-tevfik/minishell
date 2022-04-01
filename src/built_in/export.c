/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:02:07 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
#include "../../incl/protect.h"

int	add_new_export(t_list **envp, char *s1, char *s2)
{
	t_env	*env;

	env = calloc_protect(1, sizeof(*env));
	env->key = s1;
	if (s2)
		env->value = s2;
	else
		env->value = strdup_protect("");
	ft_lstadd_back(envp, lstnew_protect(env));
	return (0);
}

void	write_export_env(t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = env_lst->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env_lst = env_lst->next;
	}
}

void	free_double_chr(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		free(s1[i]);
		i++;
	}
	free(s1);
}

void	error_txt(char **argument)
{
	free_double_chr(argument);
	perror("export:not a valid identifier");
}

/*
**argument free??
*/

int	export_command(t_list **env, t_pipeline *pipe_line)
{
	char	**argument;
	int		i;
	int		exit_code;

	exit_code = 1;
	i = 0;
	if (!pipe_line->command[1])
		write_export_env(*env);
	while (pipe_line->command[i + 1])
	{
		i++;
		argument = split_protect(pipe_line->command[i], '=');
		if (!(ft_isname(argument[0])) || pipe_line->command[i][0] == '=')
		{
			error_txt(argument);
			continue ;
		}
		else if (!ft_strrchr(pipe_line->command[i], '='))
			continue ;
		else if (match_key_env(env, argument[0]) == 0)
			exit_code = add_new_export(env, argument[0], argument[1]);
	}
	return (exit_code);
}
