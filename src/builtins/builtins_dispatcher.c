/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/14 14:53:42 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "builtins.h"

const t_builtins	g_builtins[] =
{
	{ "echo", &cmd_echo},
	{ "exit", &cmd_exit},
	{ "setenv", &cmd_setenv},
	{ "unsetenv", &cmd_unsetenv},
	{ "pwd", &cmd_pwd},
	{ "cd", &cmd_cd},
	{ "true", &cmd_true},
	{ "false", &cmd_false},
	{ "type", &cmd_type},
	{ "\0", NULL}
};

static void	*dispatcher(char *cmd)
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

int		is_a_builtin(char *cmd)
{
	if (dispatcher(cmd))
		return (1);
	else
		return (0);
}

int			builtins_dispatcher(char **argv)
{
	int			(*f)(int, char**);
	int			ret;
	int			argc;

	argc = 0;
	ret = e_command_not_found;
	if ((f = dispatcher(*argv)))
	{
		while (argv[argc])
			++argc;
		ret = f(argc, argv);
	}
	return (ret);
}
