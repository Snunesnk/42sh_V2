#include "libft.h"
#include "error.h"
#include "shell.h"

int	has_redirections(int type)
{
	return (type == IO_NB
		|| type == LESS
		|| type == GREAT
		|| type == DLESS
		|| type == DGREAT
		|| type == LESSAND
		|| type == GREATAND);
}

static t_redirection	*type_less_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IOREAD;
	(*lst) = (*lst)->next;
	r->redirector.filename = get_tokvalue(*lst);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_great_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	r->instruction = IOWRITE;
	(*lst) = (*lst)->next;
	r->redirectee.filename = get_tokvalue(*lst);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_dgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	r->instruction = IOCAT;
	(*lst) = (*lst)->next;
	r->redirectee.filename = get_tokvalue(*lst);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_greatand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	int		fd;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	r->instruction = IODUP;
	(*lst) = (*lst)->next;
	r->redirectee.filename = get_tokvalue(*lst);
	if (r->redirectee.filename[0] == '-')
		r->flags |= FDCLOSE;
	else if (ft_str_is_numeric(r->redirectee.filename))
	{
		fd = ft_atoifd(r->redirectee.filename);
		if (fd >= sysconf(_SC_OPEN_MAX) || fcntl(fd, F_GETFL) < 0)
		{
			ft_printf("%s: %d: Bad file descriptor\n", g_progname, fd);
			free(r);
			return (NULL);
		}
		r->redirectee.dest = fd;
		r->flags |= DEST;
	}
	else
		r->flags |= FILENAME;
	(*lst) = (*lst)->next;
	return (r);
}

		/* NOT COMPLETE CAUSE I COULD NOT TEST IT */
static t_redirection	*type_dless_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IOHERE;
	(*lst) = (*lst)->next;
	r->redirector.hereword = get_tokvalue(*lst);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_lessand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	int		fd;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDIN_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IODUP | IOREAD;
	(*lst) = (*lst)->next;
	r->redirector.filename = get_tokvalue(*lst);
	if (r->redirector.filename[0] == '-')
		r->flags |= FDCLOSE;
	else if (ft_str_is_numeric(r->redirector.filename))
	{
		fd = ft_atoifd(r->redirector.filename);
		if (fd >= sysconf(_SC_OPEN_MAX) || fcntl(fd, F_GETFL) < 0)
		{
			ft_printf("%s: %d: Bad file descriptor\n", g_progname, fd);
			free(r);
			return (NULL);
		}
		r->redirector.dest = fd;
		r->flags |= DEST;
	}
	else
		r->flags |= FILENAME;
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*set_redirection(t_list **lst, int io_nb)
{
	int	type;

	type = get_tokentype(*lst);
	if (type == GREAT)
		return (type_great_redirection(lst, io_nb));
	else if (type == DGREAT)
		return (type_dgreat_redirection(lst, io_nb));
	else if (type == LESS)
		return (type_less_redirection(lst, io_nb));
	else if (type == DLESS)
		return (type_dless_redirection(lst, io_nb));
	else if (type == GREATAND)
		return (type_greatand_redirection(lst, io_nb));
	else if (type == LESSAND)
		return (type_lessand_redirection(lst, io_nb));
	return (NULL);
}

static t_redirection	*parse_redirection(t_list **lst)
{
	int		io_nb;

	/* Parse IO_NB if ther is one */
	if (get_tokentype(*lst) == IO_NB)
	{
		io_nb = ft_atoifd(get_tokvalue(*lst));
		(*lst) = (*lst)->next;
	}
	else
		io_nb = -1;
	return (set_redirection(lst, io_nb));
}

t_redirection	*build_redirections(t_list **lst)
{
	t_redirection	*r;
	t_redirection	**n;

	while (get_tokentype(*lst) != PIPE && get_tokentype(*lst) != END
		&& get_tokentype(*lst) != IO_NB && !is_redir_type(get_tokentype(*lst)))
		(*lst) = (*lst)->next;
	r = parse_redirection(lst);
	if (r)
		n = &(r->next);
	while (get_tokentype(*lst) != PIPE && get_tokentype(*lst) != END)
	{
		(*lst) = (*lst)->next;
 		if (get_tokentype(*lst) == IO_NB || is_redir_type(get_tokentype(*lst)))
		{
			while (has_redirections(get_tokentype(*lst)))
			{
				*n = parse_redirection(lst);
				if (*n)
					n = &((*n)->next);
			}
		}
	}
	return (r);
}

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
	r->redirector.dest = open(r->redirector.filename, O_RDONLY);
	if (r->redirector.dest < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
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
	while (r)
	{
		if (r->instruction == IOWRITE)
			do_iowrite(r);
		else if (r->instruction == IOCAT)
			do_iocat(r);
		else if (r->instruction == IOREAD)
			do_ioread(r);
		else if (r->instruction == IOHERE)
			do_iohere(r);
		else if (r->instruction == IODUP)
			do_iodup(r);
		else if (r->instruction == (IODUP | IOREAD))
			do_iodread(r);
		r = r->next;
	}
	return (0);
}

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
