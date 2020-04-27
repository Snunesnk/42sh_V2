/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:41:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/27 20:41:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	free_all_processes(t_process *p)
{
	t_process	*next_p;

	while (p)
	{
		ft_printf("process to be freed: %s\n", p->argv[0]);
		next_p = p->next;
		free_process(p);
		p = next_p;
	}
}

void	free_job(t_job **j)
{
	t_job	*j_next;
	t_job	*tmp;

	ft_printf("\n\n\t\t\t\t\t/!\\entrée/!\\\n\n");
	if (*j == g_first_job)
	{
		free_all_processes((*j)->first_process);
		free(*j);
		g_first_job = NULL;
	}
	else
	{
		j_next = g_first_job;
		while (j_next && j_next->next)
		{
			ft_printf("process test: %s\n", j_next->first_process->argv[0]);
			if (j_next->next->pgid == (*j)->pgid)
			{
				ft_printf("process retenu !!\n\n");
				tmp = j_next->next;
				j_next->next = tmp->next;
				free_all_processes(tmp->first_process);
				ft_printf("\n\n\t\t\t\t\t/!\\sortie/!\\\n\n");
				free(tmp);
				return ;
			}
			j_next = j_next->next;
		}
	}
	ft_printf("\n\n\t\t\t\t\t/!\\sortie/!\\\n\n");
}
