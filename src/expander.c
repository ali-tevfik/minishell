/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:07:24 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/01 18:08:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/commands.h"

char	*expander(char *txt, t_list *env)
{
	char	*envp_;
	char	*new_text;
	int		result;

	result = 0;
	new_text = ft_substr(txt, 0, find_space(txt));
	while (env)
	{
		envp_ = ft_split(env->content, '=')[0];
		if (!envp_)
			exit(0);
		if (ft_strncmp(new_text, envp_, ft_strlen(envp_)) == 0)
		{
			free(envp_);
			return (getenv(new_text));
		}
		free(envp_);
		env = env->next;
	}
	return (NULL);
}
