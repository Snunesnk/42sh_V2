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

t_redirection	*parse_redirections(t_list **lst)
{
	t_redirection	*r;

	r = (t_redirection*)ft_memalloc(sizeof(t_redirection));
	if (get_tokentype(*lst) == IO_NB)
	{
		r->redirector.dest = ft_atoifd(get_tokvalue(*lst));
/*		if (r->redirector.dest >= sysconf(_SC_OPEN_MAX)) //  Should be checked at launch time...
			ft_printf("%s: %s: Bad file descriptor\n", g_progname, r->redirector.dest);
*/
		(*lst) = (*lst)->next;
	}
	return (r);
}

int	do_redirection(t_process *p)
{
	(void)p;
	return (0);
}


/*
 //				if (fcntl(ft_atoi(get_tokvalue(*lst)), F_GETFL) < 0)
//				{
//					ft_printf("%s: %s: File descriptor not openm do not write on it\n", g_progname, get_tokvalue(*lst));
//				}
		}
		else if (get_tokentype(*lst) == GREAT)
		{
			if (get_tokentype((*lst)->next) == WORD)
			{
				int fd = open("./toto", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				p->redir[0].newfd = fd;
				p->redir[0].oldfd = STDOUT_FILENO;
//				ft_printf(">> ret:%d\n", (int)write(fd, "OKOKOK", 6));
//				close(fd);
			}
			*lst = (*lst)->next;
			*lst = (*lst)->next;
			return (p);
		}
*/
