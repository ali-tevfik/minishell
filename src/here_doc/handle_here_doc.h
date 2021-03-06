/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_here_doc.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:40:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/04/01 12:42:46 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_HERE_DOC_H
# define HANDLE_HERE_DOC_H

/* System headers */
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* User defined headers */
# include "../libft/libft.h"
# include "../tokenizer/tokenizer_data_structs.h"
# include "../parser/parser_data_structs.h"
# include "../parser/parser_utils.h"
# include "../../incl/protect.h"
# include "../../incl/built_in.h"
# include "../../incl/built_in_utils.h"
# include "../../incl/fork.h"

/* Global variable */
extern int	g_interactive;

/* Data structures */
typedef struct s_here_doc_params
{
	size_t	i;
	char	*eof;
}	t_here_doc_params;

/* Function prototypes */
bool	read_here_doc(t_list *pipe_list);

#endif
