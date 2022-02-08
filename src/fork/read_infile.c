/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:01 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 12:49:50 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int read_infile(t_command *command)
{
	int	id;
	id = open(command->in_file, O_RDONLY);
	if (command->redirection_operator_in == OUT){}
	else if (command->redirection_operator_in == APPEND){}
	else if (command->redirection_operator_in == READ)
		id = read(codam->in_file, O_RDONLY);
	else if (command->redirection_operator_in == HERE_DOC){}
	return (id);
}
