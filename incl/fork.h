/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 13:06:56 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 14:20:33 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

#include "../src/parser/parser_data_structs.h"
void fork_func(t_list *command_lst, char *envp[], t_list *env, int *last_id);
int	wait_and_get_last_exit_status(int last_process_pid);
#endif
