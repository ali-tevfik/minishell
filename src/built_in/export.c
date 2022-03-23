/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 13:16:48 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"
#include "../../incl/protect.h"

void	add_new_export(t_list **envp, char *s1, char *s2, bool *exit_code)
{
	t_env	*env;

	env = ft_calloc(2, sizeof(*env));
	if (!env)
		exit(-1);
	env->key = s1;
	if (s2)
		env->value = s2;
	else
		env->value = strdup_protect("");
	ft_lstadd_back(envp, ft_lstnew(env));
	exit_code = false;
}

void	write_export_env(t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = env_lst->content;
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
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

void	error_txt(char **argument, char *pipe_line_command, bool *exit_code)
{
	free_double_chr(argument);
	printf("export: `%s': not a valid identifier\n",
		pipe_line_command);
	*exit_code = true;
}

int	export_command(t_list **env, t_pipeline *pipe_line)
{
	char	**argument;
	int		i;
	bool	exit_code;

	exit_code = false;
	i = 0;
	if (!pipe_line->command[1])
		write_export_env(*env);
	while (pipe_line->command[i + 1])
	{
		i++;
		argument = split_protect(pipe_line->command[i], '=');
		if (!(ft_isname(argument[0])) || pipe_line->command[i][0] == '=')
		{
			error_txt(argument, pipe_line->command[i], &exit_code);
			continue ;
		}
		else if (!ft_strrchr(pipe_line->command[i], '='))
			continue ;
		else if (match_key_env(env, argument[0]) == 0)
			add_new_export(env, argument[0], argument[1], &exit_code);
	}
	return (exit_code);
}
