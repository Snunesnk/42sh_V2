/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 17:35:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char		**build_argv(t_list *lst, int argc)
{
	char	**argv;
	int		i;

	i = 0;
	if ((argv = (char**)ft_memalloc(sizeof(char*) * (argc + 1))))
	{
		while (lst && i < argc)
		{
			if (get_tokentype(lst) == IO_NB)
				lst = lst->next->next->next;
			if (is_redir_type(get_tokentype(lst)))
				lst = lst->next->next;
			if (get_tokentype(lst) == WORD)
			{
				if (!dup_token_value(argv, i, lst))
					return (NULL);
				++i;
			}
			if (get_tokentype(lst) == PIPE || get_tokentype(lst) == END)
				break ;
			lst = lst->next;
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
	if (*lst)
	{
		p->argc = get_argc(*lst, 0, NULL);
		p->argv = build_argv(*lst, p->argc);
		if (p->argv == NULL)
		{
			free(p);
			return (NULL);
		}
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
	int			type;

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
			break ;
		else
		{
			*p = build_a_process(lst);
			if (*p == NULL)
				return (NULL);
			p = &((*p)->next);
		}
	}
	return (first_p);
}

t_job		*build_job(t_list **lst)
{
	t_job	*j;

	j = (t_job*)ft_memalloc(sizeof(t_job));
	if (j == NULL)
		return (NULL);
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	j->first_process = build_processes(lst);
	if (j->first_process == NULL)
	{
		free(j);
		return (NULL);
	}
	return (j);
}

int			execute_job(t_list *lst, int foreground)
{
	int		ret;
	t_job	*j;

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
