/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/09/25 16:42:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_getopt.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"
#include "job_control.h"
#include "shell.h"

static int	set_envcpy(char *arg, char ***env_cpy, char *pequal)
{
	char	*name;

	*pequal = '\0';
	if (!(name = ft_strdup(arg)))
		return (e_cannot_allocate_memory);
	*pequal = '=';
	++pequal;
	ft_putenv_table(env_cpy, name, pequal, 1);
	ft_memdel((void**)&name);
	return (1);
}

int		cmd_env(int argc, t_process *p)
{
	extern char	**environ;
	char		**env_copy;
	char		*pequal;
	int		opt;
	_Bool		i;

	i = 0;
	g_opterr = 1;
	g_optind = RESET_OPTIND;
	if (argc == 1)
	{
		ft_print_tables(environ);
		return (0);
	}
	while ((opt = ft_getopt(argc, p->argv, "+i")) != -1)
	{
		if (opt == 'i')
			i |= 1;
		else if (opt == '?')
			return (125);
	}
	if (i)
	{
		if (argc == 2)
			return (0);
		env_copy = NULL;
	}
	else
		env_copy = ft_tabcpy(environ);
	while (g_optind < argc && (pequal = ft_strstr(p->argv[g_optind], "=")))
	{
		set_envcpy(p->argv[g_optind], &env_copy, pequal);
		++g_optind;
	}
	if (p->argv[g_optind] && !is_a_builtin(p->argv[g_optind]))
	{
		ft_dprintf(p->errfile, "ENV command is broken !!!");
	/*	opt = launch_job(&p->argv[g_optind], env_copy); */
	}
	else
	{
		psherror(e_invalid_input, "[builtin [argument...]]", e_cmd_type);
		ft_dprintf(p->errfile, "Usage: env [-i] [name=value]... [utility [argument...]]\n");
		opt = 1;
	}
	ft_tabdel(&env_copy);
	return (opt);
}
