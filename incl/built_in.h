/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:19:32 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/28 15:14:06 by adoner        ########   odam.nl         */
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
# include "built_in_utils.h"

t_list	*create_env_list(char *envp[]);
int		pwd_command(t_pipeline *pipeline);
int		echo_command(t_pipeline *pipe_line);
int		env_command(t_list *envp);
int		export_command(t_list **envp, t_pipeline *pipe_line);
int		unset_command(t_list **envp, t_pipeline *pipe_line);
t_list	*delete_env(t_list *old_lst, t_list **envp);
int		cd_command(char *where, t_list *env);
void	add_new_export(t_list **envp, char *s1, char *s2, bool *exit_code);
void	exit_command(t_pipeline *pipeline, int *exit_code);

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;
#endif
