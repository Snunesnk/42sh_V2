/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:03:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/17 11:39:29 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

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
		ft_putstr_fd("unalias: no argument\n", 2);
	else
	{
		ret = SUCCESS;
		if (!(argv = unalias_opt(argc, argv)))
			return (FAILURE);
		while (*argv)
		{
			if (unset_shell_var(*argv, &g_alias) == FAILURE)
			{
				ft_dprintf(2, "unalias: %s: not found\n", *argv);
				ret = FAILURE;
			}
			++argv;
		}
	}
	return (ret);
}
