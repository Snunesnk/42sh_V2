#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "job_control.h"

void	print_p(t_process *p)
{
	while (p)
	{
		ft_print_tables(p->argv);
		p = p->next;
	}
}

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

char		**build_argv(t_list **lst)
{
	t_token	*t;
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
	}
	return (argv);
}

t_process	*build_a_process(t_list **lst)
{
	t_process	*p;
	t_token		*t;
	char		**argv;

	p = (t_process*)ft_memalloc(sizeof(t_process));
	while (*lst)
	{
		p->argv = build_argv(lst);
		if (p->argv == NULL)
			return (NULL);
		else
			return (p);
	}
	return (NULL);
}

t_process	*build_processes(t_list **lst)
{
	t_process	*first_process;
	t_process	*p;
	t_token		*t;


	first_process = build_a_process(lst);
	p = first_process;
	while (*lst)
	{
		while (*lst && (t = (*lst)->content) && t->type != WORD)
			(*lst) = (*lst)->next;
		p = p->next;
		p = build_a_process(lst);
		if (p == NULL)
			return (NULL);
/*		printf("--- next job ---\n");  //Debug
		ft_print_tables(p->argv);      //Debug
*/	}
	return (first_process);
}

t_job	*build_a_job(t_list **lst)
{
	t_job	*j;
	t_token	*t;

	j = NULL;
	while (*lst)
	{
		j = (t_job*)ft_memalloc(sizeof(t_job));
		if (j == NULL)
			return (NULL);
		j->first_process = build_processes(lst);
		print_p(j->first_process); /* debug */
		while (*lst && (t = (*lst)->content) && t->type != WORD)
			(*lst) = (*lst)->next;
	}
	return (j);

}

t_job	*build_jobs(t_list **lst)
{
	return (build_a_job(lst));
}

int	execute_line(t_list *lst)
{
	t_job		*j;
	t_process	*p;

	lst = lst->next;
	j = build_jobs(&lst);
	while (j)
	{
		p = j->first_process;
		while (p)
		{
			ft_print_tables(p->argv);
			p = p->next;
		}
		j = j->next;
	}
	exit(21);
/*	launch_job(t_job *j, int foreground)
*/
/*	launch_job(j, 1);
*/
	return (SUCCESS);
}
