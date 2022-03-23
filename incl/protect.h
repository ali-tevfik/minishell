/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 16:47:21 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 18:55:49 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTECT_H
# define PROTECT_H

# include "../src/libft/libft.h"

char	**split_protect(char *txt, char ch);
char	*join_protect(char *s1, char *s2);
char	*strdup_protect(char *s1);
char	*substr_protect(char *s1, int start, int finish);
char	*substr_protect(char *s1, int start, int finish);
void	*calloc_protect(size_t count, size_t size);
t_list	*lstnew_protect(void *content);
void	protect_dup2(int fd, int i);
void	protect_close(int id);
char	*protect_itoa(int i);
#endif
