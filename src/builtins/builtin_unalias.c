/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:03:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/21 08:22:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

static char	**unalias_opt(int argc, char **argv)
{
	int	opt;
	int	unset_all;

	unset_all = 0;
	g_opterr = 1;
	g_optind = 1;
	while ((opt = ft_getopt(argc, argv, "a")) != -1)
	{
		if (opt == 'a')
			unset_all = 1;
		else if (opt == '?')
			return (NULL);
	}
	if (unset_all)
		ft_lstdel(&g_alias, del_env);
	return (argv + g_optind);
}

int			cmd_unalias(int argc, char **argv)
{
	int			ret;

	ret = FAILURE;
	if (argc == 1)
		pbierror("no argument");
	else
	{
		ret = SUCCESS;
		if (!(argv = unalias_opt(argc, argv)))
			return (FAILURE);
		while (*argv)
		{
			if (unset_shell_var(*argv, &g_alias) == FAILURE)
			{
				pbierror("%s: not found", *argv);
				ret = FAILURE;
			}
			++argv;
		}
	}
	return (!!ret);
}
