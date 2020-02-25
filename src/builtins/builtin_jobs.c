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
	if (j)
	{
		if (job_is_stopped(j))
			ft_dprintf(STDERR_FILENO, "[%d]%c\t%s\t%s\n", i, tip, "Stopped", j->command);
		else
			ft_dprintf(STDERR_FILENO, "[%d]%c\t%s\t%s\n", i, tip, "Running", j->command);
		j = j->next;
	}
	return (0);
}
