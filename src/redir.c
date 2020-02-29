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

t_redirection	*set_redirection(t_list **lst, int io_nb)
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
	else if (type == GREATAND || type == ANDGREAT)
		return (type_greatand_redirection(lst, io_nb));
	else if (type == LESSAND || type == ANDLESS)
		return (type_lessand_redirection(lst, io_nb));
	return (NULL);
}
