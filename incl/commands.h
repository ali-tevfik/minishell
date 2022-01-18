#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"
# include <errno.h>
# define PATH_MAX 1024

void cd_command(char *where);
void pwd_command(void);
char *skip_space(char *s);
# endif
