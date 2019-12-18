/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 09:35:14 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "job_control.h"
#include "builtins.h"

static int	part_sep(int argc, t_process *p)
{
	extern char	**environ;
	unsigned char	status;

	status = g_retval;
	if (!ft_strcmp("--", p->argv[1]))
	{
		if (argc == 2)
		{
 /* It will leaks because functions below do not properly free */
/*			ft_tabdel(&p->argv);
			ft_tabdel(&environ);
			free_all_shvar(); */
			ft_dprintf(p->errfile, "exit\n");
			exit(status);
		}
		return (2);
	}
	return (1);
}

static int	numarg_exit(int argc, t_process *p, int i)
{
	extern char	**environ;
	unsigned char	status;

	ft_dprintf(p->errfile, "exit\n");
	if (argc > i + 1)
	{
		ft_dprintf(p->errfile,
		"%s: %s: too many arguments\n",	g_progname, p->argv[0]);
		return (1);
	}
	status = (unsigned char)ft_atoi(p->argv[i]);
 /* It will leaks because functions below do not properly free */
/*	ft_tabdel(&p->argv);
	ft_tabdel(&environ);
	free_all_shvar();
*/	exit(status);
}

static void	nomatter_exit(t_process *p, int i)
{
	extern char	**environ;

	ft_dprintf(p->errfile, "exit\n");
	ft_dprintf(p->errfile,
	"%s: %s: %s: numeric argument required\n",
			g_progname, p->argv[0], p->argv[i]);
 /* It will leaks because functions below do not properly free */
/*	ft_tabdel(&p->argv);
	ft_tabdel(&environ);
	free_all_shvar();
*/	exit(2);
}

int		cmd_exit(int argc, t_process *p)
{
	extern char	**environ;
	unsigned char	status;
	int		i;

	status = g_retval;
	if (argc > 1)
	{
		i = part_sep(argc, p);
		if (*p->argv[i]
			&& (((*p->argv[i] == '-' || *p->argv[i] == '+') && ft_str_is_numeric(&p->argv[i][i]))
			|| ft_str_is_numeric(p->argv[i])) && ft_strcmp("--", p->argv[i]))
			return (numarg_exit(argc, p, i));
		else
			nomatter_exit(p, i);
	}
 /* It will leaks because functions below do not properly free */
/*	ft_tabdel(&p->argv);
	ft_tabdel(&environ);
	free_all_shvar();
*/	ft_dprintf(p->errfile, "exit\n");
	exit(status);
}
