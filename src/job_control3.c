/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 10:53:54 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/19 14:18:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

void		wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	if (!g_job_control_enabled)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		while (!mark_process_status(pid, status) && !job_is_completed(j))
			pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
	else
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		while (!mark_process_status(pid, status) && !job_is_stopped(j)
				&& !job_is_completed(j))
			pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		ft_putchar_fd('\n', g_dis.fd);
}

void		format_job_info(t_job *j, const char *status)
{
	t_process	*p;
	int			sig;

	p = j->first_process;
	sig = -1;
	while (p && p->stopped == 0)
		p = p->next;
	if (p && p->stopped == 1)
	{
		if (WIFSIGNALED(p->status))
			sig = WTERMSIG(p->status);
		else if (WIFSTOPPED(p->status))
			sig = WSTOPSIG(p->status);
	}
	if (sig == SIGINT || sig == SIGQUIT)
		return ;
	else if (strsig(sig) && ft_strcmp("Done", status))
	{
		ft_dprintf(STDERR_FILENO, "\n[%ld] %s(%s) \t %s\n",
			(long)j->pgid, status, strsig(sig), j->command);
	}
	else
		ft_dprintf(STDERR_FILENO, "\n[%ld] %s \t %s\n",
				(long)j->pgid, status, j->command);
}

static void	do_job_innerloop(t_job **j, t_job **jlast, t_job **jnext)
{
	if (job_is_completed(*j))
	{
		format_job_info(*j, "Done");
		if (*jlast)
		{
			free_job(*j);
			(*jlast)->next = *jnext;
		}
		else
		{
			free_job(*j);
			g_first_job = *jnext;
		}
	}
	else if (job_is_stopped(*j) && !(*j)->notified)
	{
		format_job_info(*j, "Stopped");
		(*j)->notified = 1;
		*jlast = *j;
	}
	else
		*jlast = *j;
}

void		do_job_notification(t_job *j, t_job *jlast, t_job *jnext)
{
	update_status();
	while (j)
	{
		jnext = j->next;
		do_job_innerloop(&j, &jlast, &jnext);
		j = jnext;
	}
}

int			are_stopped_jobs(void)
{
	t_job	*j;

	j = g_first_job;
	while (j)
	{
		if (job_is_stopped(j))
			return (1);
		j = j->next;
	}
	return (0);
}
