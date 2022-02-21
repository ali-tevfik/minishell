/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:57:17 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/21 14:40:20 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/built_in.h"
#include "../../incl/minishell.h"
#include "../parser/parser_data_structs.h"

void	cd_command(char *where, t_list *env)
{
	int		result;
	char	*old_pwd;

	result = 0;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		exit(-1);
	if (where == NULL)
		where = expander("HOME", env);
	else if (!match_str(where, "-"))
		result = chdir(expander("OLDPWD", env));
	else
		result = chdir(where);
	if (result == -1)
		printf("minishell: cd: %s: %s\n", where, strerror(errno));
	else
	{
		match_key_env(&env, "OLDPWD");
		add_new_export(&env, "OLDPWD", old_pwd);
	}
}
