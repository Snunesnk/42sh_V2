/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/11 21:27:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

t_job		*find_lastbackgrounded(void)
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

static int	two_arg_case(char **argv)
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

static int	single_arg_case(void)
{
	t_job	*j;

	if ((j = find_lastbackgrounded()))
	{
		update_status();
		if (job_is_completed(j))
		{
			pbierror("job has terminated");
			return (1);
		}
		ft_printf("%s\n", j->command);
		put_job_in_foreground(j, 1);
		return (get_exit_value(get_job_status(j, 1)));
	}
	else
	{
		pbierror("current: no such job");
		return (1);
	}
}

int			cmd_fg(int argc, char **argv)
{
	if (g_shell_pgid != getpgid(getpid()) ||
		!g_job_control_enabled || !g_shell_is_interactive)
	{
		return (g_errordesc[psherror(e_no_job_control,
				argv[0], e_cmd_type)].code);
	}
	if (argc == 1)
		return (single_arg_case());
	else if (argc == 2)
		return (two_arg_case(argv));
	else
		return (pbierror("usage: %s [job_spec]", g_builtin_name));
	return (0);
}
