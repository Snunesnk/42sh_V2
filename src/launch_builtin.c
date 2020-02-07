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

	if (p->redir != NULL)
		p->redir->flags |= NOFORK;
	/* 1. Set redirections */
	do_redirection(p->redir);

	/* Execute the builtin. Retreive return value */
	ret = builtins_dispatcher(p->argv);

	/* 2. Undo redirections */
	undo_redirection(p->redir);

	/* Retreive return value */
	return (ret);
}
