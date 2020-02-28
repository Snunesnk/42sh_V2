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

static void	tag_all_redirections(t_redirection *r)
{
	while (r)
	{
		r->flags |= NOFORK;
		r = r->next;
	}
}

int	launch_builtin(t_process *p)
{
	int ret;

	if (p->redir != NULL)
		tag_all_redirections(p->redir);
	/* 1. Set redirections */
	if ((ret = do_redirection(p->redir)))
		return (g_errordesc[ret].code);
	/* Execute the builtin. Retreive return value */
	ret = builtins_dispatcher(p->argv);
	ft_printf("NORMAL\n");
	/* 2. Undo redirections */
	undo_redirection(p->redir);

	/* Retreive return value */
	return (ret);
}
