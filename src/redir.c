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
	(void)lst;
	ft_printf("\nIN PARSING REDIR\n\n");
	return (NULL);
}

int	do_redirection(t_process *p)
{
	(void)p;
	return (0);
}


/*
		else if (get_tokentype(*lst) == IO_NB)
		{
			if (ft_atoifd(get_tokvalue(*lst)) >= sysconf(_SC_OPEN_MAX))
			{
				ft_printf("%s: %s: Bad file descriptor\n", g_progname, get_tokvalue(*lst));
 //				if (fcntl(ft_atoi(get_tokvalue(*lst)), F_GETFL) < 0)
//				{
//					ft_printf("%s: %s: Bad file descriptor\n", g_progname, get_tokvalue(*lst));
//				}
			}
			else
			{
				printf("test");
			}
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
