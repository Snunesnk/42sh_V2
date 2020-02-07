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
	if (do_redirection(p->redir))
		exit(EXIT_FAILURE); /* redirection failure, error msg have to be implemented */

	/* Execute the builtin. Retreive return value */
	ret = builtins_dispatcher(p->argv);

	/* 2. Undo redirections */
	if (undo_redirection(p->redir))
		exit(EXIT_FAILURE); /* redirection failure, error msg have to be implemented */

	/* Retreive return value */
	return (ret);
}
