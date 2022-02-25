/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:19:32 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/25 16:59:02 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"
# include <errno.h>
# include <limits.h>
# include <string.h>
# include "../src/parser/parser_data_structs.h"

t_list	*add_envp(char *envp[]);
void	pwd_command(t_pipeline *pipeline);
void	echo_command(t_pipeline *pipe_line);
void	env_commands(t_list *envp);
void	export_command(t_list **envp, t_pipeline *pipe_line);
void	unset_command(t_list **envp, t_pipeline *pipe_line);
int		match_key_env(t_list **envp, char *argument);
t_list	*delete_env(t_list *old_lst, t_list **envp);
char	*expander(char *txt, t_list *env);
char	*get_env(t_list *lst, char *argument);
int		match_str(char *s1, char *s2);
void	cd_command(char *where, t_list *env);
int		ft_isname(char *txt);
void	add_new_export(t_list **envp, char *s1, char *s2);
void	one_argument(t_pipeline *pip_line, t_list *env,
		char *envp[], int *lastid);
void	built_in(t_pipeline *pipeline, t_list **env);
int		check_built_in_file(t_pipeline *pipeline);
int		write_outfile(t_pipeline *pipe_line);
void	exit_command(char *value);

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;
#endif
