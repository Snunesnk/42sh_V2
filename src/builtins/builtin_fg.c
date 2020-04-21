/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 08:21:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

t_job	*find_lastbackgrounded(void)
{
	t_job	*j;

	j = g_first_job;
	while (j && j->next)
	{
		j = j->next;
		ft_printf("BREAK\n");
	}
	if (j)
		return (j);
	return (NULL);
}

int		cmd_fg(int argc, char **argv)
{
	t_job	*j;

	if (argc == 1)
	{
		if ((j = find_lastbackgrounded()))
			put_job_in_foreground(j, 1);
		else
		{
			pbierror("current: no such job");
			return (1);
		}
	}
	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_foreground(j, 1);
	}
	else
		return (pbierror("usage: %s [job_spec]",
			g_builtin_name));
	return (0);
}
