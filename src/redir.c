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
/*
static t_redirection	*type_less_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	char		*content;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->redirector.dest = io_nb;
	r->flags = O_CREAT | O_APPEND | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	r->redirectee.filename = content;
	(*lst) = (*lst)->next;
	content = get_tokvalue(*lst);
	return (r);
}
*/
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

	r->redirector.dest = io_nb;

	r->instruction = GREAT;
	r->flags = O_CREAT | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	(*lst) = (*lst)->next; /* Go to next token which is inevitably a word */
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
/*
static t_redirection	*type_dgreat_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	char		*content;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->flags = O_CREAT | O_APPEND | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	r->redirectee.filename = content;
	(*lst) = (*lst)->next;
	content = get_tokvalue(*lst);
}
*/
/* This construct allows both the standard output (file descriptor 1) and the
** standard error output (file descriptor 2) to be redirected to the file whose
** name is the expansion of word.
**
** There are two formats for redirecting standard output and standard error:
**
**        &>word
** and,
**        >&word
**
** When using the second form, word may not expand to a number or ‘-’. If it does,
** other redirection operators apply (see Duplicating File Descriptors below) for
** compatibility reasons.
*/
/*
static t_redirection	*type_greatand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	char		*content;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->flags = O_CREAT | O_APPEND | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	r->redirectee.filename = content;
	(*lst) = (*lst)->next;
	content = get_tokvalue(*lst);
}
*/
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
/*
static t_redirection	*type_dless_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	char		*content;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->flags = O_CREAT | O_APPEND | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	r->redirectee.filename = content;
	(*lst) = (*lst)->next;
	content = get_tokvalue(*lst);
}
*/
/* Duplicating File Descriptors
** It is used to duplicate input file descriptors. If word expands to one
** or more digits, the file descriptor denoted by n is made to be a copy
** of that file descriptor. If the digits in word do not specify a file
** descriptor open for input, a redirection error occurs. If word evaluates
** to ‘-’, file descriptor n is closed. If n is not specified, the standard input (file descriptor 0) is used.
**
** The redirection operator: [n]<&word
*/
/*
static t_redirection	*type_lessand_redirection(t_list **lst, int io_nb)
{
	t_redirection	*r;
	char		*content;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	r->flags = O_CREAT | O_APPEND | O_WRONLY;
	r->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	r->redirectee.filename = content;
	(*lst) = (*lst)->next;
	content = get_tokvalue(*lst);
}
*/
static t_redirection	*set_redirection(t_list **lst, int io_nb)
{
	int	type;

	type = get_tokentype(*lst);
	if (type == GREAT)
		return (type_great_redirection(lst, io_nb));
/*	else if (type == DGREAT)
		return (type_dgreat_redirection(lst, io_nb));
	else if (type == LESS)
		return (type_less_redirection(lst, io_nb));
	else if (type == DLESS)
		return (type_dless_redirection(lst, io_nb));
	else if (type == GREATAND)
		return (type_greatand_redirection(lst, io_nb));
	else if (type == LESSAND)
		return (type_lessand_redirection(lst, io_nb));
*/	return (NULL);
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
		io_nb = STDOUT_FILENO;
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

/*
int	do_redirection(t_process *p)
{
	(void)p;
	return (0);
}
*/

/*		if (r->redirector.dest >= sysconf(_SC_OPEN_MAX)) //  Should be checked at launch time...
			ft_printf("%s: %s: Bad file descriptor\n", g_progname, r->redirector.dest);
*/
/*                              // Way to check if file descriptor exists and is open.
 //				if (fcntl(ft_atoi(get_tokvalue(*lst)), F_GETFL) < 0)
//				{
//					ft_printf("%s: %s: File descriptor not openm do not write on it\n", g_progname, get_tokvalue(*lst));
*/
