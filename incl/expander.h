/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 15:45:41 by adoner        #+#    #+#                 */
/*   Updated: 2022/03/23 14:19:56 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

int	check_dolar_waar(char *str, int chr);
int	finished_expander(char *txt);
int	check_quotes(char *line, char ch);
int	check_emtpy_dolar(char *line);
char	*crete_first_deel(char *line);
char	*skip_space(char *line);
int	find_how_many_chr(char *line);
#endif
