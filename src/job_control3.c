/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/27 21:02:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

void		wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status) && !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void		format_job_info(t_job *j, const char *status)
{
	ft_dprintf(STDERR_FILENO, "%ld (%s): %s\n",
			(long)j->pgid, status, j->command);
}

static void	do_job_innerloop(t_job **j, t_job **jlast, t_job **jnext)
{
	if (job_is_completed(*j))
	{
		format_job_info(*j, "completed");
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
		format_job_info(*j, "stopped");
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
