#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "job_control.h"
#include "token.h"

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
void	ft_print_tables(char **tables)
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
}

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
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	build_a_process(t_process **p, t_list **lst)
{
	*p = (t_process*)ft_memalloc(sizeof(t_process));
	while (*lst)
	{
		if (build_argv(&((*p)->argv), lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	build_processes(t_process **first_process, t_list **lst)
{
	t_process	*p;
	t_token		*t;

	if (build_a_process(first_process, lst) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	p = *first_process;
	while (*lst)
	{
		while (*lst && (t = (*lst)->content) && t->type == PIPE)
			(*lst) = (*lst)->next;
		if (t->type != WORD)
			return (EXIT_SUCCESS);
		if (*lst == NULL)
			break;
		if (build_a_process(&(p->next), lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		p = p->next;
/*		printf("--- next job ---\n");  //Debug
		ft_print_tables(p->argv);      //Debug
*/	}
/*	printf("ALL:\n");
	print_p(first_process);
*/	return (EXIT_SUCCESS);
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
		return (EXIT_FAILURE);
	if (build_processes(&((*j)->first_process), lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
/*		print_p((*j)->first_process); */
	return (EXIT_SUCCESS);

}

int	build_jobs(t_job **j, t_list **lst)
{
	t_job	*newj;
	t_token	*t;

	if (build_a_job(&newj, lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*j = newj;
	while (*lst)
	{
		t = (*lst)->content;
		if (t->type == SEMICOLON)
			(*lst) = (*lst)->next;
		else
			break;
		if (build_a_job(&(newj->next), lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		newj = newj->next;
	}
	return (EXIT_SUCCESS);
}

int	launch_all_jobs(t_list *lst)
{
	t_job		*j_beg;
	t_job		*j;

	lst = lst->next;
	j = NULL;
	if (build_jobs(&j, &lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (j)
	{
		j_beg = j->next;
		launch_job(j, 1);
		free_job(j);
		j = j_beg;
	}
	return (EXIT_SUCCESS);
}
