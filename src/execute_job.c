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

char	*get_tokvalue(t_list *lst)
{
	t_token	*t;

	t = lst->content;
	return (t->value);
}

int	get_tokentype(t_list *lst)
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
	if (*lst)
	{
		p->argv = build_argv(lst);
		if (p->argv == NULL)
		{
			free(p);
			return (NULL);
		}
		if (has_redirections(get_tokentype(*lst)))
		{
			/* Add redirection instruction calling parse_redirection */
			p->redir = build_redirections(lst);
		}
		return (p);
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

int	execute_job(t_list *lst, int foreground)
{
	t_job		*j;

	lst = lst->next;
	j = NULL;
	j = build_job(&lst);
	if (j == NULL)
		return (FAILURE);
	first_job = j; /* Here is the thing to change for a queue that is being updated */
	launch_job(j, foreground);
	free_job(j);
	return (SUCCESS);
}
