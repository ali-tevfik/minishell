/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 15:15:14 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/25 18:36:43 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void	export_command(t_list *envp, char *line)
{
	char	*argument;

	argument = ft_strdup(skip_space(line + 6));
	if (ft_strrchr(argument, '=') == 0)
		return ;
	if (!ft_isalpha(argument[0]))
		return ;
	if (!argument)
		exit(0);
	ft_lstadd_back(&envp, ft_lstnew(argument));
}
