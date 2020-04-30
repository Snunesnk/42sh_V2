/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/28 13:52:49 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

const t_builtins	g_builtins[] =
{
	{ "echo", &cmd_echo},
	{ "exit", &cmd_exit},
	{ "setenv", &cmd_export},
	{ "unsetenv", &cmd_unset},
	{ "cd", &cmd_cd},
	{ "fg", &cmd_fg},
	{ "bg", &cmd_bg},
	{ "jobs", &cmd_jobs},
	{ "true", &cmd_true},
	{ "false", &cmd_false},
	{ "type", &cmd_type},
	{ "hash", &cmd_hash},
	{ "fc", &cmd_fc},
	{ "export", &cmd_export},
	{ "unset", &cmd_unset},
	{ "set", &cmd_set},
	{ "alias", &cmd_alias},
	{ "unalias", &cmd_unalias},
	{ "env", &cmd_env},
	{ "builtin", &cmd_builtin},
	{ "\0", NULL}
};

static void		*dispatcher(char *cmd)
{
	int	i;

	i = 0;
	while (g_builtins[i].key[0] && ft_strcmp(cmd, g_builtins[i].key))
		++i;
	if (!(g_builtins[i].key[0]))
		return (NULL);
	else
		return ((void*)g_builtins[i].f);
}

int				is_a_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (dispatcher(cmd))
		return (1);
	else
		return (0);
}

int				is_a_builtin_command(char **command)
{
	if (!command)
		return (0);
	while (is_valid_assignment(*command))
		++command;
	return (is_a_builtin(*command));
}

int				builtins_dispatcher(char **argv)
{
	int			(*f)(int, char**);
	int			ret;
	int			argc;

	argc = 0;
	ret = e_command_not_found;
	if ((f = dispatcher(*argv)))
	{
		g_builtin_name = *argv;
		while (argv[argc])
			++argc;
		ret = f(argc, argv);
	}
	return (ret);
}
