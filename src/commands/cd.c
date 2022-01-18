#include "../../incl/commands.h"
#include "../../incl/minishell.h"

void cd_command(char *where)
{
	int result;

	result = chdir(skip_space(where + 2));
	if (result == -1)
		perror("Error: ");
}
