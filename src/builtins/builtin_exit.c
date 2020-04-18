/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 16:22:46 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		part_sep(int argc, char **argv)
{
	unsigned char	status;

	status = g_retval;
	if (!ft_strcmp("--", argv[1]))
	{
		if (argc == 2)
		{
			ft_tabdel(&argv);
			free_hist();
			ft_dprintf(STDERR_FILENO, "exit\n");
			exit_clean(status);
		}
		return (2);
	}
	return (1);
}

static int		numarg_exit(int argc, char **argv, int i)
{
	unsigned char	status;

	status = g_retval;
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (argc > i + 1)
	{
		ft_dprintf(STDERR_FILENO,
				"%s: %s: too many arguments\n", g_progname, argv[0]);
		return (1);
	}
	status = (unsigned char)ft_atoi(argv[i]);
	ft_tabdel(&argv);
	free_hist();
	return (exit_clean(status));
}

static void		nomatter_exit(char **argv, int i)
{

	ft_dprintf(STDERR_FILENO, "exit\n");
	ft_dprintf(STDERR_FILENO,
	"%s: %s: %s: numeric argument required\n",
			g_progname, argv[0], argv[i]);
	ft_tabdel(&argv);
	free_hist();
	exit_clean(2);
}

int				cmd_exit(int argc, char **argv)
{
	unsigned char	status;
	int				i;

	status = g_retval;
	if (argc > 1)
	{
		i = part_sep(argc, argv);
		if (*argv[i]
	&& (((*argv[i] == '-' || *argv[i] == '+') && ft_str_is_numeric(&argv[i][i]))
			|| ft_str_is_numeric(argv[i])) && ft_strcmp("--", argv[i]))
			return (numarg_exit(argc, argv, i));
		else
			nomatter_exit(argv, i);
	}
	ft_tabdel(&argv);
	free_hist();
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (exit_clean(status));
}
