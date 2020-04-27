/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/27 10:49:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

void            print_jobs(void);


t_job	*find_lastbackgrounded(void)
{
	t_job	*jlast;
	t_job	*j;

	j = g_first_job;
	jlast = NULL;
	while (j)
	{
		if (j->pgid)
			jlast = j;
		j = j->next;
	}
	if (jlast)
		return (jlast);
	return (NULL);
}

int		cmd_fg(int argc, char **argv)
{
	t_job	*j;

	if (!g_shell_is_interactive)
		return (g_errordesc[psherror(e_no_job_control, argv[0], e_cmd_type)].code);
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
		if (j == NULL)
		{
			pbierror("%d: no such job", ft_atoi(argv[1]));
			return (1);
		}
		put_job_in_foreground(j, 1);
	}
	else
	{
		return (pbierror("usage: %s [job_spec]",
					g_builtin_name));
	}
	return (0);
}
