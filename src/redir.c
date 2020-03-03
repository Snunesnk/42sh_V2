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
		|| type == ANDGREAT
		|| type == LESSAND
		|| type == GREATAND);
}

static int	has_close_at_end(char *str)
{
	int	i;

	if ((i = ft_strlen(str)) > 0)
		--i;
	if (str[i] == '-')
	{
		str[i] = '\0';
		return (1);
	}
	else
		return (0);
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

static t_redirection	*subtype_great_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (io_nb == -1)
		r->redirector.dest = STDOUT_FILENO;
	else
		r->redirector.dest = io_nb;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
	(*lst) = (*lst)->next;
	return (r);
}

static t_redirection	*type_great_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = subtype_great_redirection(lst, io_nb);
	r->instruction = IOWRITE;
	return (r);
}

static t_redirection	*type_dgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;

	r = subtype_great_redirection(lst, io_nb);
	r->instruction = IOCAT;
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
	if (has_close_at_end(r->redirectee.filename))
		r->flags |= AMBIGU;
	else
		treat_single_exp(&(r->redirectee.filename), 1);
	if (r->redirectee.filename[0] == '-' && r->redirectee.filename[2] == '\0')
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
		r->redirector.dest = ft_atoifd(r->redirector.filename);
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
	r->instruction = IODUP | IOWRITE;
	(*lst) = (*lst)->next;
	r->redirectee.filename = ft_strdup(get_tokvalue(*lst));
	treat_single_exp(&(r->redirectee.filename), 1);
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
	return (NULL);
}
