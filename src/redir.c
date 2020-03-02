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
		|| type == ANDLESS
		|| type == ANDGREAT
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
	/* make a copy */
	r->redirector.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirector.filename), 1);
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
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
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
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_greatand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	r->instruction = IODUP;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
	if (r->redirectee.filename[0] == '-')
		r->flags |= FDCLOSE;
	else if (ft_str_is_numeric(r->redirectee.filename))
	{
		r->redirectee.dest = ft_atoifd(r->redirectee.filename);
		r->flags |= DEST;
	}
	else
		r->flags |= FILENAME;
	(*lst) = (*lst)->next;
	return (r);
}

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
	r->redirector.hereword = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirector.filename), 0); /* Tilde expansions should not be taken into account */
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
	r->redirector.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirector.filename), 1);
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

static t_redirection	*type_andless_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	int		fd;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirectee.dest = STDOUT_FILENO;
	else
		r->redirectee.dest = io_nb;
	r->instruction = IODUP | IOREAD;
	(*lst) = (*lst)->next;
	r->redirector.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirector.filename), 1);
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

static t_redirection	*type_andgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	(void)io_nb;
	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->redirectee.dest = STDOUT_FILENO;
	r->instruction = IODUP | IOWRITE;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
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
	else if (type == GREATAND)
		return (type_greatand_redirection(lst, io_nb));
	else if (type == LESSAND)
		return (type_lessand_redirection(lst, io_nb));
	else if (type == ANDGREAT)
		return (type_andgreat_redirection(lst, io_nb));
	else if (type == ANDLESS)
		return (type_andless_redirection(lst, io_nb));
	return (NULL);
}
