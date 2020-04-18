/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 03:00:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				cmd_unsetenv(int argc, char **argv)
{
	char	*builtin_name;

	builtin_name = argv[0];
	if (argc == 1)
	{
		ft_dprintf(STDERR_FILENO, "%s: usage: %s name ...\n",
			builtin_name, builtin_name);
		return (FAILURE);
	}
	while (*++argv)
	{
		if (!**argv || ft_strchr(*argv, '='))
			ft_dprintf(STDERR_FILENO, "%s: `%s': not a valid identifier\n",
				builtin_name, *argv);
		else
			flag_shell_var(*argv, EXPORT >> SHVAR_RM_OFF, g_env);
	}
	return (SUCCESS);
}
