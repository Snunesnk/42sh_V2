/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:41:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 17:42:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	free_all_processes(t_process *p)
{
	t_process	*next_p;

	while (p)
	{
		next_p = p->next;
		free_process(p);
		p = next_p;
	}
}

void	free_job(t_job *j)
{
	t_job	*j_next;
	t_job	*tmp;

	if (j == g_first_job)
	{
		free_all_processes(j->first_process);
		free(j);
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
				free_all_processes(tmp->first_process);
				free(tmp);
				return ;
			}
			j_next = j_next->next;
		}
	}
}
