/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:32:50 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/17 18:29:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

static int		do_unset(char **args)
{
	int	ret;

	ret = e_success;
	while (args && *args)
	{
		if (!is_valid_identifier(*args, NULL))
		{
			pbierror("'%s': not a valid identifier", *args);
			ret = 1;
		}
		else
			unset_shell_var(*args, &g_env);
		++args;
	}
	return (ret);
}

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
	return (do_unset(args));
}
