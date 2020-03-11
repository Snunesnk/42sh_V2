/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 19:37:27 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job	*find_lastbackgrounded(void)
{
	t_job	*j;

	j = first_job;
	while (j && j->next)
	{
		j = j->next;
		ft_printf("BREAK\n");
	}
	if (j)
		return (j);
	return (NULL);
}

int	cmd_fg(int argc, char **argv)
{
	t_job	*j;

	if (argc == 1)
	{
		if ((j = find_lastbackgrounded()))
			put_job_in_foreground(j, 1);
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: current: no such job\n",
					g_progname, argv[0]);
			return (1);
		}
	}
	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_foreground(j, 1);
	}
	else
		ft_dprintf(STDERR_FILENO, "fg: usage: fg [job_spec]\n");
	return (0);
}
