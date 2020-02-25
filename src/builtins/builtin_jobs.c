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

int	cmd_jobs(int argc, char **argv)
{
	int	i;
	char	tip;
	t_job	*j;

	(void)argc;
	(void)argv;
	i = 1;
	j = first_job;
	tip = '+';
	update_status();
	while (j->next)
	{
	//	ft_dprintf("[%d] %c %s %s\n", i, <current>, j->state, j->command);
		if (job_is_stopped(j))
			ft_dprintf(STDERR_FILENO, "[%d]%c\t%s\t%s\n", i, tip, "Stopped", j->command);
		else
			ft_dprintf(STDERR_FILENO, "[%d]%c\t%s\t%s\n", i, tip, "Running", j->command);
		j = j->next;
	}
	return (0);
}
