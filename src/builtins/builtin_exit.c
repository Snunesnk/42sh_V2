/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/22 14:15:21 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int	g_noexit = 0;

static void		print_exit(void)
{
	if (!g_noexit)
		ft_dprintf(STDERR_FILENO, "exit\n");
}

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
			print_exit();
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
	print_exit();
	if (argc > i + 1)
	{
		pbierror("too many arguments");
		return (1);
	}
	status = (unsigned char)ft_atoi(argv[i]);
	ft_tabdel(&argv);
	free_hist();
	return (exit_clean(status));
}

static void		nomatter_exit(char **argv, int i)
{
	print_exit();
	pbierror("%s: numeric argument required", argv[i]);
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
	if (g_shell_is_interactive && g_hist)
		free_hist();
	print_exit();
	return (exit_clean(status));
}
