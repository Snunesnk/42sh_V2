/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:41:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/01 14:44:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		free_all_processes(t_process *p)
{
	t_process	*next_p;

	while (p)
	{
		next_p = p->next;
		free_process(p);
		p = next_p;
	}
}

void		free_a_job(t_job *j)
{
	free_all_processes(j->first_process);
	free(j->command);
	free(j);
}

void		free_job(t_job *j)
{
	t_job	*j_next;
	t_job	*tmp;

	if (j == g_first_job)
	{
		free_a_job(j);
		g_first_job = NULL;
	}
	else
	{
		j_next = g_first_job;
		while (j_next && j_next->next)
		{
			if (j_next->next->pgid == j->pgid)
			{
				tmp = j_next->next;
				j_next->next = tmp->next;
				free_a_job(tmp);
				return ;
			}
			j_next = j_next->next;
		}
	}
}

static char	*join_cmd(char *s1, char *s2)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	free(s1);
	return (s);
}

char		*commandline(t_list *lst)
{
	char	*cmd;
	int		type;

	cmd = ft_strdup("");
	while (lst)
	{
		type = get_tokentype(lst);
		if (type == WORD || type == IO_NB)
			cmd = join_cmd(cmd, get_tokvalue(lst));
		else
			cmd = join_cmd(cmd, g_tokval[type]);
		if (type != IO_NB && lst->next)
			cmd = join_cmd(cmd, " ");
		lst = lst->next;
	}
	return (cmd);
}
