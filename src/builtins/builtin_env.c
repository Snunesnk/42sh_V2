/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 18:17:17 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/22 19:39:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

int			g_is_motherfucking_env = 0;

static int	exec_env_command(char **argv)
{
	char	**envp;
	int		ret;

	ret = 0;
	envp = get_env_tab();
	argv = ft_tabcpy(argv);
	restore_procmask();
	if (argv)
		ret = execute_env_process(argv, envp, NULL, NULL);
	ft_tabdel(&envp);
	ft_tabdel(&argv);
	return (ret);
}

static int	print_env_var(t_shell_var *svar)
{
	if ((svar->flag & EXPORT) && svar->value)
	{
		ft_printf("%s=%s\n", svar->name, svar->value);
		return (0);
	}
	return (1);
}

static char	**env_opt(int argc, char **argv)
{
	int	opt;

	g_opterr = 1;
	g_optind = 1;
	while ((opt = ft_getopt(argc, argv, "+i")) != -1)
	{
		if (opt == 'i')
			empty_env(&g_env);
		else if (opt == '?')
		{
			pbierror("usage: %s [name[=value] ...] [-i [command]]",
			g_builtin_name);
			return (NULL);
		}
	}
	return (argv + g_optind);
}

static int	get_env_options_and_assignments(int argc, char ***argv)
{
	int	ret;

	ret = 0;
	if (!(*argv = env_opt(argc, *argv)))
		ret = 2;
	while (!ret && **argv && is_valid_assignment(**argv))
	{
		ret = set_temp_variable(**argv);
		++(*argv);
	}
	return (ret);
}

int			cmd_env(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc && (ret = get_env_options_and_assignments(argc, &argv)))
		return (ret);
	if (argv[0] == NULL)
		print_shell_var(g_env, print_env_var);
	else
		ret = exec_env_command(argv);
	unset_temp_shell_variables();
	return (ret);
}
