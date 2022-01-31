/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:07:24 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/31 15:34:39 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "../incl/commands.h"

int	expander(char *txt, t_list *env)
{
	 char *new_text;
	printf("%d\n", find_space(txt));
	new_text = ft_substr(txt, 0, find_space(txt));
	printf("new text [%s]\n", new_text);
	env = env->next;
	while(env)
	{
		if (ft_strncmp(new_text, env->content, ft_strlen(new_text)) == 0)
		{
			printf("bulundu [%s]\n", getenv(new_text));
		}
		env = env->next;
	}
	return (find_space(txt));
}
