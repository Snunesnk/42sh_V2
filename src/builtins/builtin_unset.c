/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:32:50 by efischer          #+#    #+#             */
/*   Updated: 2020/04/17 11:36:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

int				cmd_unset(int ac, char **args)
{
	int		ret;
	int		option;

	++args;
	option = 1;
	if (ac > 1 && (ret = get_next_opt(&args, "v")) != -1)
	{
		if (ret != 'v')
		{
			ft_dprintf(STDERR_FILENO, "./21sh: unset: -%c: invalid option\n", \
					ret);
			ft_putendl_fd("unset: usage: unset [-v] [arg ...]", 2);
			return (e_invalid_input);
		}
		option++;
	}
	while (args && *args)
		unset_shell_var(*args++, &g_env);
	return (e_success);
}
