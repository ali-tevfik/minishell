/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_outfile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:43:40 by adoner        #+#    #+#                 */
/*   Updated: 2022/02/08 12:50:55 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int write_outfile(t_command *command)
{
	int	id;

	if (command->redirection_operator_out == OUT){
		id = open(command->out_file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	else if (command->redirection_operator_out == APPEND){}
	else if (command->redirection_operator_out == READ){}
	else if (command->redirection_operator_out == HERE_DOC){}
	return (id);
}
