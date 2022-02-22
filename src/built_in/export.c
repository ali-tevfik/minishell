/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/22 17:25:51 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void	add_new_export(t_list **envp, char *s1, char *s2)
{
	t_env	*env;

	env = ft_calloc(2, sizeof(env));
	if (!env)
		exit(-1);
	env->key = s1;
	if (s2)
		env->value = s2;
	else
		env->value = ft_strdup("");
	ft_lstadd_back(envp, ft_lstnew(env));
}

void	write_export_env(t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = env_lst->content;
		printf("declare -x %s=%s\n", env->key, env->value);
		env_lst = env_lst->next;
	}
}

void	export_command(t_list **env, t_pipeline *pipe_line)
{
	char	**argument;
	int		i;

	i = 0;
	if (!pipe_line->command[1])
		write_export_env(*env);
	while (pipe_line->command[i + 1])
	{
		i++;
		argument = ft_split(pipe_line->command[i], '=');
		if (!argument)
			exit(0);
		if (!(ft_isname(argument[0])))
		{
			printf("export: `%s': not a valid identifier\n",
				pipe_line->command[i]);
			continue ;
		}
		else if (!ft_strrchr(pipe_line->command[i], '='))
			continue ;
		else if (match_key_env(env, argument[0]) == 0)
			add_new_export(env, argument[0], argument[1]);
	}
}
