#include "libft.h"
#include "error.h"
#include "shell.h"

/* ************************************************* **
**                                                   **
**             UNDO REDIRECTIONS                     **
**                                                   **
** ************************************************* */

static int	undo_iowrite(t_redirection *r)
{
	dup2(r->save, r->redirector.dest);
	close(r->save);
	return (0);
}

static int	undo_ioread(t_redirection *r)
{
	dup2(r->save, r->redirectee.dest);
	close(r->save);
	return (0);
}

int	undo_redirection_internal(t_redirection *r)
{
	while (r)
	{
		if (r->flags & REDSUC)
		{
			if (r->instruction == IOWRITE)
				undo_iowrite(r);
			else if (r->instruction == IOCAT)
				undo_iowrite(r);
			else if (r->instruction == IOREAD)
				undo_ioread(r);
			else if (r->instruction == IODUP && !(r->flags & FDCLOSE))
				undo_iowrite(r);
			else if (r->instruction == (IODUP | IOREAD) && !(r->flags & FDCLOSE))
				undo_ioread(r);
		}
		r = r->next;
	}
	return (0);
}

int	undo_redirection(t_redirection *r)
{
	while (r)
	{
		undo_redirection_internal(r);
		/* should we free at that point ? */
		r = r->next;
	}
	return (0);
}
