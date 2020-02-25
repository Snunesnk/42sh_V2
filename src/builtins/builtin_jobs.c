/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	https://pubs.opengroup.org/onlinepubs/9699919799/utilities/jobs.html
*/

#include "shell.h"

static void	display_signo(char c, int status, t_job *j)
{
	if (WSTOPSIG(status) == SIGTSTP)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTSTP) %s\n", j->pgid, c, j->command);
	else if (WSTOPSIG(status) == SIGSTOP)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGSTOP) %s\n", j->pgid, c, j->command);
	else if (WSTOPSIG(status) == SIGTTIN)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTTIN) %s\n", j->pgid, c, j->command);
	else if (WSTOPSIG(status) == SIGTTOU)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTTOU) %s\n", j->pgid, c, j->command);
	else
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(?) %s\n", j->pgid, c, j->command);
}

static void	display_exit_no(char c, int status, t_job *j)
{
	int	ret;

	ret = WEXITSTATUS(status);
	if (ret)
		ft_dprintf(STDERR_FILENO, "[%d] %c Done(%d) %s\n", j->pgid, c, ret, j->command);
	else
		ft_dprintf(STDERR_FILENO, "[%d] %c Done %s\n", j->pgid, c, j->command);
}

static char	set_current(int job_number)
{
	if (job_number == 0)
		return ('+');
	else if (job_number == 1)
		return ('-');
	return (' ');
}

int	cmd_jobs(int argc, char **argv)
{
	int	job_number;
	char	current;
	int	status;
	t_job	*j;

	(void)argc;
	(void)argv;
	job_number = 0;
	j = first_job;
	update_status();
	while (j->next)
	{ /* "[%d] %c %s %s\n", <job-number>, <current>, <state>, <command> */
		current = set_current(job_number);
		if (job_is_stopped(j))
		{
			status = get_job_status(j, 1);
			if (WIFSTOPPED(status))
				display_signo(current, status, j);
		}
		else if (job_is_completed(j))
		{
			status = get_job_status(j, 1);
			if (WIFEXITED(status))
				display_exit_no(current, status, j);
		}
		else
			ft_dprintf(STDERR_FILENO, "[%d] %c %s %s\n", j->pgid, current, "Running", j->command);
		j = j->next;
		++job_number;
	}
	return (0);
}
