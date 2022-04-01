/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 13:06:56 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/31 16:32:26 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H
# include "../src/parser/parser_data_structs.h"

typedef struct s_dup2
{
	int	fd[2];
	int	end_file;
	int	*last_id;
}				t_dup2;

void	fork_func(t_list *command_lst, t_list *env, int *last_id);
int		wait_and_get_last_exit_status(int last_process_pid);
void	handle_redirections(t_pipeline *pipe_line);
void	kies_builtin_of_execve(t_pipeline *pip_line, t_list *env);
void	first_child(t_pipeline *pip_line, t_list *env, int fd[2]);
void	middle_child(t_pipeline *pip_line, t_list *env, int fd[2], int endfile);
void	last_child(t_pipeline *pip_line, t_list *env, int fd[2], int *lastid);
void	one_argument(t_pipeline *pip_line, t_list *env, int *lastid);
#endif
