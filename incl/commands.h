/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:45 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 14:38:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"
# include <errno.h>
# include <limits.h>
# include <string.h>

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
char	*get_env(t_list *lst, char *argument);

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;
#endif
