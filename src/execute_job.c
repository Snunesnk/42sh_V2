/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:54:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/******************************************************
**                                                   **
**                 BUILD JOBS/PROCESS UTILS          **
**                                                   **
******************************************************/

/* Debugg function */
void	print_p(t_process *p)
{
	while (p)
	{
		ft_print_tables(p->argv);
		p = p->next;
	}
}

int	is_redir_type(int type)
{
	return (type == GREATAND
		|| type == LESSAND
		|| type == ANDGREAT
		|| type == DGREAT
		|| type == DLESS
		|| type == GREAT
		|| type == LESS);
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

/******************************************************
**                                                   **
**                 BUILD PROCESSES                   **
**                                                   **
******************************************************/

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
		else if (t->type == IO_NB)
		{
			lst = lst->next->next->next;
			if (lst)
			{
				t = lst->content;
				if (t->type == WORD)
					++argc;
				else
					continue;
			}
		}
		else if (is_redir_type(t->type))
		{
			lst = lst->next->next;
			if (lst)
			{
				t = lst->content;
				if (t->type == WORD)
					++argc;
				else
					continue;
			}
		}
		else
			break;
		if (lst)
			lst = lst->next;
		else
			break;
	}
	return (argc);
}

char	**build_argv(t_list *lst, int argc)
{
	char	**argv;
	int	i;

	i = 0;
	argv = (char**)ft_memalloc(sizeof(char*) * (argc + 1));
	if (argv != NULL)
	{
		while (lst && i < argc)
		{
			if (get_tokentype(lst) == IO_NB)
				lst = lst->next->next->next;
			if (is_redir_type(get_tokentype(lst)))
				lst = lst->next->next;
			if (get_tokentype(lst) == WORD)
			{
				argv[i] = get_tokvalue(lst);
				++i;
			}
			if (get_tokentype(lst) == PIPE || get_tokentype(lst) == END)
				break;
			lst = lst->next;
		}
	//	ft_printf("i:%d argc:%d\n", i, argc);
	//	ft_print_tables(argv);
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
		p->argc = get_argc(*lst);
		p->argv = build_argv(*lst, p->argc);
		if (p->argv == NULL)
		{
			free(p);
			return (NULL);
		}
		/* Add redirection instruction calling parse_redirection */
		if (*lst)
			p->redir = build_redirections(lst);
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
		else if (!*lst)
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

/******************************************************
**                                                   **
**                 BUILD JOBS                        **
**                                                   **
******************************************************/

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

/******************************************************
**                                                   **
**                 EXECUTE JOBS                      **
**                                                   **
******************************************************/

int	execute_job(t_list *lst, int foreground)
{
	int		ret;
	t_job		*j;

	if (lst == NULL)
		return (EXIT_FAILURE);
	j = NULL;
	j = build_job(&lst);
	if (j == NULL)
		return (FAILURE);
	add_job_to_queue(j);
	ret = launch_job(j, foreground);
	if (ret == -1)
		ret = get_exit_value(get_job_status(j, foreground));
	if (foreground)
		free_job(j);
	g_retval = ret;
	return (ret);
}
