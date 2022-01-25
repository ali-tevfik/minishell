/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:45 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/25 12:16:52 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"
# include <errno.h>
# define PATH_MAX 1024

t_list	*add_envp(char *envp[]);
void	cd_command(char *where);
void	pwd_command(void);
char	*skip_space(char *s);
void	echo_command(char *text);
int		skip_space_start(char *s);
void	env_commands(t_list *envp);

#endif
