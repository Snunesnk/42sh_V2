/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bookeeping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/14 16:49:15 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

void	mark_job_as_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void	continue_job(t_job *j, int foreground)
{
	mark_job_as_running(j);
	if (foreground)
		put_job_in_foreground(j, 1);
	else
		put_job_in_background(j, 1);
}

int		get_job_status(t_job *j, int foreground)
{
	t_process	*p;
	int			status;

	status = 0;
	if (!foreground)
		return (0);
	p = j->first_process;
	while (p)
	{
		status = p->status;
		p = p->next;
	}
	return (status);
}

int		get_exit_value(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_dprintf(STDERR_FILENO, "Quit\n");
		return (sig + 128);
	}
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status) + 128);
	else
		return (128);
}

void	add_job_to_queue(t_job *j)
{
	t_job	*j_next;

	if (g_first_job)
	{
		j_next = g_first_job;
		while (j_next->next)
			j_next = j_next->next;
		j_next->next = j;
	}
	else
		g_first_job = j;
}
