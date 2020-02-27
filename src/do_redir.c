#include "libft.h"
#include "error.h"
#include "shell.h"

/* ************************************************* **
**                                                   **
**               DO REDIRECTIONS                     **
**                                                   **
** ************************************************* */

static int	do_iowrite(t_redirection *r)
{
	r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	if (r->flags & NOFORK)
		r->save = dup(r->redirector.dest);
	dup2(r->redirectee.dest, r->redirector.dest);
	close(r->redirectee.dest);
	return (0);
}

static int	do_iocat(t_redirection *r)
{
	r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r->redirectee.dest < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	if (r->flags & NOFORK)
		r->save = dup(r->redirector.dest);
	dup2(r->redirectee.dest, r->redirector.dest);
	close(r->redirectee.dest);
	return (0);
}

static int	do_ioread(t_redirection *r)
{
	if (access(r->redirector.filename, F_OK))
	{
		psherror(e_no_such_file_or_directory, r->redirector.filename, e_cmd_type);
		return (e_no_such_file_or_directory);
	}
	if (access(r->redirector.filename, R_OK))
	{
		psherror(e_permission_denied, r->redirector.filename, e_cmd_type);
		return (e_permission_denied);
	}
	r->redirector.dest = open(r->redirector.filename, O_RDONLY);
	if (r->redirector.dest < 0)
	{
		psherror(e_system_call_error, r->redirector.filename, e_cmd_type);
		return (e_system_call_error);
	}
	if (r->flags & NOFORK)
		r->save = dup(r->redirectee.dest);
	dup2(r->redirector.dest, r->redirectee.dest);
	close(r->redirector.dest);
	return (0);
}

static int	do_iohere(t_redirection *r)
{
	if (write(r->redirectee.dest, r->redirector.hereword, ft_strlen(r->redirector.hereword)) < 0)
	{
		ft_printf("\nWRITE ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	return (0);
}

static int	do_iodup(t_redirection *r)
{
	if (r->flags & FDCLOSE)
		close(r->redirector.dest);
	else if (r->flags & FILENAME)
	{
		r->redirectee.dest = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (r->redirectee.dest < 0)
		{
			ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
			return (1);
		}
		if (r->flags & NOFORK)
			r->save = dup(r->redirector.dest);
		dup2(r->redirectee.dest, r->redirector.dest);
		close(r->redirectee.dest);
	}
	else if (r->flags & DEST)
	{
		if (r->flags & NOFORK)
			r->save = dup(r->redirector.dest);
		dup2(r->redirectee.dest, r->redirector.dest);
		close(r->redirectee.dest);
	}
	return (0);
}

static int	do_iodread(t_redirection *r)
{
	if (r->flags & FDCLOSE)
		close(r->redirectee.dest);
/*	else if (r->flags & FILENAME)
	{ // Ambiguous redirection
		r->redirector.dest = open(r->redirector.filename, O_RDONLY);
		if (r->redirector.dest < 0)
		{
			ft_printf("\nOPEN ERRRROOOORRR\n\n");
			return (1);
		}
		dup2(r->redirector.dest, r->redirectee.dest);
		close(r->redirector.dest);
	}
*/	else if (r->flags & DEST)
	{
		if (r->flags & NOFORK)
			r->save = dup(r->redirectee.dest);
		dup2(r->redirector.dest, r->redirectee.dest);
		close(r->redirector.dest);
	}
	return (0);
}

int	do_redirection(t_redirection *r)
{
	/* Used for error type and displaying the correct error message in process.c */
	int		error;
	t_redirection	*beg;

	beg = r;
	error = 0;
	while (r)
	{
		ft_printf("REDIREC\n");
		if (r->instruction == IOWRITE)
			error = do_iowrite(r);
		else if (r->instruction == IOCAT)
			error = do_iocat(r);
		else if (r->instruction == IOREAD)
			error = do_ioread(r);
		else if (r->instruction == IOHERE)
			error = do_iohere(r);
		else if (r->instruction == IODUP)
			error = do_iodup(r);
		else if (r->instruction == (IODUP | IOREAD))
			error = do_iodread(r);
		if (error)
		{
			if (r->flags & NOFORK)
				undo_redirection(beg);
			ft_printf("ERROR\n");
			return (error);
		}
		r->flags |= REDSUC;
		r = r->next;
	}
	return (0);
}
