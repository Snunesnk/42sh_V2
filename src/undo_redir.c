#include "libft.h"
#include "error.h"
#include "shell.h"

/* Debugg */
static void	debug_r(t_redirection *r)
{
	static int	i;

	i = 0;
	ft_printf("\n");
//	while (r)
//	{
		ft_printf("\nUNDO redir:%d\n", i++);
		ft_printf("\tr->redirectee.dest: %d\n", r->redirectee.dest);
		ft_printf("\tr->save: %d\n", r->save);
		r = r->next;
//	}
//	ft_printf("\n");
}

static int	undo_iowrite(t_redirection *r, int *shell_fd)
{
	if (r->redirector.dest < 3 && !shell_fd[r->redirector.dest])
	{
		shell_fd[r->redirector.dest] = 1;
		dup2(r->save, r->redirector.dest);
	}
	else if (r->redirector.dest >= 3 && shell_fd[r->redirector.dest])
		dup2(r->save, r->redirector.dest);
	close(r->save);
	return (0);
}

static int	undo_ioread(t_redirection *r, int *shell_fd)
{
	debug_r(r); /* Debug */
	/* Multiple close of STDIN are done */
	/* HERE IS THE HUGE BUG CLOSING STDIN multiple times, need fcntl to check ?*/
	if (r->redirectee.dest < 3 && !shell_fd[r->redirectee.dest])
	{
		shell_fd[r->redirectee.dest] = 1;
		dup2(r->save, r->redirectee.dest);
	}
	else if (r->redirectee.dest >= 3 && shell_fd[r->redirectee.dest])
		dup2(r->save, r->redirectee.dest);
	close(r->save);
	return (0);
}

int	undo_redirection_internal(t_redirection *r)
{
	int	shell_fd[3];

	shell_fd[0] = 0;
	shell_fd[1] = 0;
	shell_fd[2] = 0;
	while (r)
	{
		if (r->flags & REDSUC)
		{
			if (r->instruction == IOWRITE)
				undo_iowrite(r, shell_fd);
			else if (r->instruction == IOCAT)
				undo_iowrite(r, shell_fd);
			else if (r->instruction == IOREAD)
				undo_ioread(r, shell_fd);
			else if (r->instruction == IODUP && !(r->flags & FDCLOSE))
				undo_iowrite(r, shell_fd);
			else if (r->instruction == (IODUP | IOREAD) && !(r->flags & FDCLOSE))
				undo_ioread(r, shell_fd);
		}
		r = r->next;
	}
	return (0);
}

int	undo_redirection(t_redirection *r)
{
	if (r)
	{
		undo_redirection_internal(r);
		/* should we free at that point ? */
		r = r->next;
	}
	return (0);
}
