/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:32:50 by efischer          #+#    #+#             */
/*   Updated: 2020/04/21 08:28:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

int				cmd_unset(int ac, char **args)
{
	int		ret;
	int		option;

	option = 1;
	++args;
	if (ac > 1 && (ret = get_next_opt(&args, "v")) != -1)
	{
		if (ret != 'v')
		{
			pbierror("-%c: invalid option", ret);
			pbierror("usage: unset [-v] [arg ...]");
			return (e_invalid_input);
		}
		option++;
	}
	while (args && *args)
		unset_shell_var(*args++, &g_env);
	return (e_success);
}
