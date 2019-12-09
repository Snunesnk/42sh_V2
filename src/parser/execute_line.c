#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "job_control.h"

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

t_job	*build_a_job(t_list **lst)
{
	t_job	*j;
	t_token	*t;

	j = (t_job*)ft_memalloc(sizeof(t_job));
	while (*lst)
	{
		j->first_process = build_a_process(lst);
		ft_print_tables(j->first_process->argv);
		printf("--- next job ---\n");
		while (*lst && (t = (*lst)->content) && t->type != WORD)
			(*lst) = (*lst)->next;
	}
	exit(21);
	return (NULL);

}

int	execute_line(t_list *lst)
{
	t_job	*newjob;
	t_job	*j;

	lst = lst->next;
	j = NULL;
	while (lst)
	{
		if ((newjob = build_a_job(&lst)) != NULL)
		{
			if (j == NULL)
				j = newjob;
			else
				j->next = newjob;
		}
		else
			exit(21);
	}

/*	launch_job(t_job *j, int foreground)
*/
/*	launch_job(j, 1);
*/
	return (SUCCESS);
}
