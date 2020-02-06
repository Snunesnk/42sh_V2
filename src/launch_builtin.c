#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"
#include "builtins.h"

int	launch_builtin(t_process *p)
{
	int ret;

	/* 1. Set redirections */


	/* Execute the builtin. Retreive return value */
	ret = builtins_dispatcher(p->argv);

	/* 2. Undo redirections */


	/* Retreive return value */
	return (ret);
}
