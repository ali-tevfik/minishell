/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:19:32 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 13:55:22 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include "../src/parser/parser_data_structs.h"

t_list	*create_env_list(char *envp[]);
int		pwd_command(t_pipeline *pipeline);
void	echo_command(t_pipeline *pipe_line);
void	env_command(t_list *envp);
int		export_command(t_list **envp, t_pipeline *pipe_line);
int		unset_command(t_list **envp, t_pipeline *pipe_line);
int		match_key_env(t_list **envp, char *argument);
t_list	*delete_env(t_list *old_lst, t_list **envp);
char	*expander(char *txt, t_list *env);
char	*get_env(t_list *lst, char *argument);
bool	strings_are_equal(char *s1, char *s2);
int		cd_command(char *where, t_list *env);
int		ft_isname(char *txt);
void	add_new_export(t_list **envp, char *s1, char *s2, bool *exit_code);
void	one_argument(t_pipeline *pip_line, t_list *env, int *lastid);
int		execute_builtin(t_pipeline *pipeline, t_list **env);
bool	is_builtin(t_pipeline *pipeline);
void	exit_command(t_pipeline *pipeline, int *exit_code);

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;
#endif
