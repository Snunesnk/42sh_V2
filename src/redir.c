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

/* Redirection of input causes the file whose name results from the expansion
** of word to be opened for reading on file descriptor n, or the standard
** input (file descriptor 0) if n is not specified.
**
** The general format for redirecting input is: [n]<word
*/
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

/* Redirection of output causes the file whose name results from the expansion
** of word to be opened for writing on file descriptor n, or the standard output
** (file descriptor 1) if n is not specified. If the file does not exist it is
** created; if it does exist it is truncated to zero size.
**
** The general format for redirecting output is: [n]>[|]word
*/
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

/* Redirection of output in this fashion causes the file whose name results from
** the expansion of word to be opened for appending on file descriptor n, or the
** standard output (file descriptor 1) if n is not specified. If the file does
** not exist it is created.
**
** The general format for appending output is: [n]>>word
*/
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

/* This construct allows both the standard output (file descriptor 1) and the
** standard error output (file descriptor 2) to be redirected to the file whose
** name is the expansion of word.
**
** There are two formats for redirecting standard output and standard error:
**
**        [n]&>word
** and,
**        [n]>&word
**
** When using the second form, word may not expand to a number or ‘-’. If it does,
** other redirection operators apply (see Duplicating File Descriptors below) for
** compatibility reasons.
*/
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
		r->flags = FDCLOSE;
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
		r->flags = DEST;
	}
	else
		r->flags = FILENAME;
	(*lst) = (*lst)->next;
	return (r);
}

/* This type of redirection instructs the shell to read input from the current
** source until a line containing only word (with no trailing blanks) is seen.
** All of the lines read up to that point are then used as the standard input
** (or file descriptor n if n is specified) for a command.
**
** The format of here-documents is:
**                                     [n]<<[-]word
**                                             here-document
**                                     delimiter
**
** No expansions done on here-doc.
** If the redirection operator is ‘<<-’, then all leading tab characters are
** stripped from input lines and the line containing delimiter. This allows
** here-documents within shell scripts to be indented in a natural fashion.
*/
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

/* Duplicating File Descriptors
** It is used to duplicate input file descriptors. If word expands to one
** or more digits, the file descriptor denoted by n is made to be a copy
** of that file descriptor. If the digits in word do not specify a file
** descriptor open for input, a redirection error occurs. If word evaluates
** to ‘-’, file descriptor n is closed. If n is not specified, the standard input (file descriptor 0) is used.
**
** The redirection operator: [n]<&word
*/
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
		r->flags = FDCLOSE;
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
		r->flags = DEST;
	}
	else
		r->flags = FILENAME;
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

	r = parse_redirection(lst);
	n = &(r->next);
	while (has_redirections(get_tokentype(*lst)))
	{
		*n = parse_redirection(lst);
		n = &((*n)->next);
	}
	return (r);
}

static int	do_iowrite(t_redirection *r)
{
	int	fd;

	fd = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	dup2(fd, r->redirector.dest);
	close(fd);
	return (0);
}

static int	do_iocat(t_redirection *r)
{
	int	fd;

	fd = open(r->redirectee.filename, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	dup2(fd, r->redirector.dest);
	close(fd);
	return (0);
}

static int	do_ioread(t_redirection *r)
{
	int	fd;

	fd = open(r->redirector.filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
		return (1);
	}
	dup2(fd, r->redirectee.dest);
	close(fd);
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
	int	fd;

	if (r->flags == FDCLOSE)
		close(r->redirectee.dest);
	else if (r->flags == FILENAME)
	{
		fd = open(r->redirectee.filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd < 0)
		{
			ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
			return (1);
		}
		dup2(fd, r->redirector.dest);
		close(fd);
	}
	else if (r->flags == DEST)
	{
		dup2(r->redirectee.dest, r->redirector.dest);
		close(r->redirectee.dest);
	}
	return (0);
}

static int	do_iodread(t_redirection *r)
{
	int	fd;

	if (r->flags == FDCLOSE)
		close(r->redirector.dest);
	else if (r->flags == FILENAME)
	{
		fd = open(r->redirector.filename, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("\nOPEN ERRRROOOORRR\n\n"); /* should be in error mgt */
			return (1);
		}
		dup2(fd, r->redirectee.dest);
		close(fd);
	}
	else if (r->flags == DEST)
	{
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

int	undo_redirection(t_redirection *r)
{
	while (r)
	{
	/* Do something here */
		/* should we free at that point ? */
		r = r->next;
	}
	return (0);
}
