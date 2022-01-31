/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:45 by adoner        #+#    #+#                 */
/*   Updated: 2022/01/31 17:42:04 by adoner        ########   odam.nl         */
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
void	export_command(t_list **envp, char *line);
void	unset_command(t_list **envp, char *argument);
int		match_key_env(t_list **envp, char *argument, int where);
t_list	*delete_env(t_list *old_lst, t_list **envp);
char	*expander(char *txt, t_list *env);
int		find_space(char *txt);

#endif
