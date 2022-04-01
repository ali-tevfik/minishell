/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_utils.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:03:22 by adoner        #+#    #+#                 */
/*   Updated: 2022/04/01 12:46:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_UTILS_H
# define BUILT_IN_UTILS_H
# include "../src/parser/parser_data_structs.h"

int		match_key_env(t_list **envp, char *argument);
char	*expander(char *txt, t_list *env);
char	*get_env(t_list *lst, char *argument);
bool	strings_are_equal(char *s1, char *s2);
int		ft_isname(char *txt);
void	one_argument(t_pipeline *pip_line, t_list *env, int *lastid);
int		execute_builtin(t_pipeline *pipeline, t_list **env, int exit_code);
bool	is_builtin(t_pipeline *pipeline);
int		built_in_and_infile_check(t_pipeline *pipeline, t_list *pipe_lst);
void	print_error(char *command, char *text);
#endif
