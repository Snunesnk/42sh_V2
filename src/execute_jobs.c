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

int		get_argc(t_list *lst)
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

char		*get_tokvalue(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->value);
}

int		get_tokentype(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->type);
}

int		build_argv(char ***argv, t_list **lst)
{
	int	argc;
	int	i;

	i = 0;
	argc = get_argc(*lst);
	*argv = (char**)ft_memalloc(sizeof(char*) * (argc + 1));
	if (*argv != NULL)
	{
		while (*lst && i < argc)
		{
			(*argv)[i] = get_tokvalue(*lst);
			++i;
			(*lst) = (*lst)->next;
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

int	build_a_process(t_process **p, t_list **lst)
{
	*p = (t_process*)ft_memalloc(sizeof(t_process));
	(*p)->infile = -1;
	(*p)->outfile = -1;
	(*p)->errfile = -1;
	if (*lst)
	{
		if (build_argv(&((*p)->argv), lst) == FAILURE)
			return (FAILURE);
		else if (get_tokentype(*lst) == IO_NB)
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
				(*p)->outfile = fd;
				(*p)->errfile = fd;
		/*		ft_printf(">> ret:%d\n", (int)write(fd, "OKOKOK", 6));
				close(fd);
		*/	}
			return (SUCCESS);
		}
		else
		{
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	build_processes(t_process **first_process, t_list **lst)
{
	t_process	*p;
	t_token		*t;

	if (build_a_process(first_process, lst) == FAILURE)
	{
		return (FAILURE);
	}
	p = *first_process;
	while (*lst)
	{
		while (*lst && (t = (*lst)->content) && t->type == PIPE)
			(*lst) = (*lst)->next;
		if (t->type != WORD)
			return (SUCCESS);
		if (*lst == NULL)
			break;
		if (build_a_process(&(p->next), lst) == FAILURE)
			return (FAILURE);
		p = p->next;
/*		printf("--- next job ---\n");  //Debug
		ft_print_tables(p->argv);      //Debug
*/	}
/*	printf("ALL:\n");
	print_p(first_process);
*/	return (SUCCESS);
}

int	build_a_job(t_job **j, t_list **lst)
{
	*j = (t_job*)ft_memalloc(sizeof(t_job));
	/* try simple pipe */
	(*j)->stdin = STDIN_FILENO;
	(*j)->stdout = STDOUT_FILENO;
	(*j)->stderr = STDERR_FILENO;
	/* end config */
	if (*j == NULL)
		return (FAILURE);
	if (build_processes(&((*j)->first_process), lst) == FAILURE)
		return (FAILURE);
/*		print_p((*j)->first_process); */
	return (SUCCESS);

}

int	build_jobs(t_job **j, t_list **lst)
{
	t_job	*newj;
	t_token	*t;

	if (build_a_job(&newj, lst) == FAILURE)
		return (FAILURE);
	*j = newj;
	while (*lst)
	{
		t = (*lst)->content;
		if (t->type == SEMI)
			(*lst) = (*lst)->next;
		else
			break;
		if (build_a_job(&(newj->next), lst) == FAILURE)
			return (FAILURE);
		newj = newj->next;
	}
	return (SUCCESS);
}

int	launch_all_jobs(t_list *lst)
{
	t_job		*j_beg;
	t_job		*j;

	lst = lst->next;
	j = NULL;
	if (build_jobs(&j, &lst) == FAILURE)
		return (FAILURE);
	while (j)
	{
		j_beg = j->next;
		launch_job(j, 1);
		free_job(j);
		j = j_beg;
	}
	return (SUCCESS);
}
