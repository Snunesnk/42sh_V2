/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/02 11:38:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

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

int		two_arg_case(char **argv)
{
	t_job	*j;

	j = find_job(ft_atoi(argv[1]));
	if (j == NULL)
	{
		pbierror("%d: no such job", ft_atoi(argv[1]));
		return (1);
	}
	if (!ft_str_is_numeric(argv[1]))
	{
		pbierror("%s: no such job", argv[1]);
		return (1);
	}
	put_job_in_foreground(j, 1);
	return (0);
}

int		cmd_fg(int argc, char **argv)
{
	t_job	*j;

	if (!g_job_control_enabled || !g_shell_is_interactive)
	{
		return (g_errordesc[psherror(e_no_job_control,
				argv[0], e_cmd_type)].code);
	}
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
	else if (argc == 2)
		return (two_arg_case(argv));
	else
		return (pbierror("usage: %s [job_spec]", g_builtin_name));
	return (0);
}
