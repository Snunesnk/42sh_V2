#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "shell.h"

/* Debugg function */
void	print_p(t_process *p)
{
	while (p)
	{
		ft_print_tables(p->argv);
		p = p->next;
	}
}

/* Debugg function */
/*void	ft_print_tables(char **tables)
{
	size_t	i;

	i = 0;
	if (tables)
	{
		while (tables[i])
		{
			printf("[%s], ", tables[i]);
			++i;
		}
		printf("\n");
	}
}*/

static int	get_argc(t_list *lst)
{
	t_token	*t;
	int	argc;

	argc = 0;
	while (lst)
	{
		t = lst->content;
		if (t->type == WORD)
			++argc;
		else
			break;
		lst = lst->next;
	}
	return (argc);
}

static char	*get_tokvalue(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->value);
}

static int	get_tokentype(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->type);
}

char	**build_argv(t_list **lst)
{
	char	**argv;
	int	argc;
	int	i;

	i = 0;
	argc = get_argc(*lst);
	argv = (char**)ft_memalloc(sizeof(char*) * (argc + 1));
	if (argv != NULL)
	{
		while (*lst && i < argc)
		{
			argv[i] = get_tokvalue(*lst);
			++i;
			(*lst) = (*lst)->next;
		}
		return (argv);
	}
	return (NULL);
}

t_process	*build_a_process(t_list **lst)
{
	t_process	*p;

	p = (t_process*)ft_memalloc(sizeof(t_process));
	if (p == NULL)
		return (NULL);
	/* Set redirections of the process if encounter >> > < << + IO_NB or WORD i.e. FILENAME */
	ft_bzero(p->redir, 10 * sizeof(t_redirection));
/*	p->infile = -1;
	p->outfile = -1;
	p->errfile = -1; */
	/* End redirections of process */
	if (*lst)
	{
		p->argv = build_argv(lst);
		if (p->argv == NULL)
		{
			free(p);
			return (NULL);
		}
		else if (get_tokentype(*lst) == IO_NB) /* Get IO_NUMBERS */
		{
			if (ft_atoifd(get_tokvalue(*lst)) >= sysconf(_SC_OPEN_MAX))
			{
				ft_printf("%s: %s: Bad file descriptor\n", g_progname, get_tokvalue(*lst));
	/*			if (fcntl(ft_atoi(get_tokvalue(*lst)), F_GETFL) < 0)
				{
					ft_printf("%s: %s: Bad file descriptor\n", g_progname, get_tokvalue(*lst));
				}
	*/		}
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
		/*		ft_printf(">> ret:%d\n", (int)write(fd, "OKOKOK", 6));
				close(fd);
		*/	}
			*lst = (*lst)->next;
			*lst = (*lst)->next;
			return (p);
		}
		else
		{
			return (p);
		}
	}
	free(p);
	return (NULL);
}

t_process	*build_processes(t_list **lst)
{
	t_process	*first_p;
	t_process	**p;
	int		type;

	first_p = build_a_process(lst);
	if (first_p == NULL)
		return (NULL);
	p = &(first_p->next);
	while (*lst)
	{
		type = get_tokentype(*lst);
		if (type == PIPE)
			(*lst) = (*lst)->next;
		else if (type == END)
			break;
		else
		{
			*p = build_a_process(lst);
			if (*p == NULL)
			{
				/* should free all processes and return NULL */
				return (NULL);
			}
			p = &((*p)->next);
		}
	}
/*	printf("ALL:\n");
	print_p(first_p);
*/	return (first_p);
}

t_job	*build_job(t_list **lst)
{
	t_job	*j;

	j = (t_job*)ft_memalloc(sizeof(t_job));
	if (j == NULL)
		return (NULL);

	/* try simple pipe */
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	/* end config */

	j->first_process = build_processes(lst);
	if (j->first_process == NULL)
	{
		free(j);
		return (NULL);
	}
	return (j);

}

int	execute_job(t_list *lst)
{
	t_job		*j;

	lst = lst->next;
	j = NULL;
	j = build_job(&lst);
	if (j == NULL)
		return (FAILURE);
	launch_job(j, 1);
	free_job(j);
	return (SUCCESS);
}
