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

#define SRUN "Running"
#define SDONE "Done"
#define SSTOP "Stopped"

static void	display_signo(int i, char c, int status, t_job *j)
{
	if (WSTOPSIG(status) == SIGTSTP)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTSTP) %s\n", i, c, j->command);
	else if (WSTOPSIG(status) == SIGSTOP)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGSTOP) %s\n", i, c, j->command);
	else if (WSTOPSIG(status) == SIGTTIN)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTTIN) %s\n", i, c, j->command);
	else if (WSTOPSIG(status) == SIGTTOU)
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(SIGTTOU) %s\n", i, c, j->command);
	else
		ft_dprintf(STDERR_FILENO, "[%d] %c Stopped(?) %s\n", i, c, j->command);
}

int	cmd_jobs(int argc, char **argv)
{
	int	i;
	char	tip;
	int	status;
	t_job	*j;

	(void)argc;
	(void)argv;
	i = 1;
	j = first_job;
	tip = '+';
	update_status();
	while (j->next)
	{ /* "[%d] %c %s %s\n", <job-number>, <current>, <state>, <command> */
		if (job_is_stopped(j))
		{
			status = get_job_status(j, 1);
			if (WIFSTOPPED(status))
				display_signo(i, tip, status, j);
		}
		else
			ft_dprintf(STDERR_FILENO, "[%d]%c\t%s\t%s\n", i, tip, "Running", j->command);
		j = j->next;
	}
	return (0);
}
