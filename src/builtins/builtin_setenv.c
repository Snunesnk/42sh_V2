/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 02:55:44 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			cmd_setenv(int argc, char **argv)
{
	char	*name;
	char	*value;
	char	*builtin_name;

	builtin_name = argv[0];
	if (argc == 1)
	{
		ft_dprintf(STDERR_FILENO, "%s: usage: %s name[=value] ...\n",
			builtin_name, builtin_name);
		return (FAILURE);
	}
	while (*++argv)
	{
		if (get_assignment(*argv, &name, &value) == SUCCESS)
			*value++ = 0;
		if (!*name || *name == '=')
			ft_dprintf(STDERR_FILENO, "%s: `%s': not a valid identifier\n",
				builtin_name, name);
		else if (value)
			set_shell_var(name, value, EXPORT >> SHVAR_ADD_OFF, &g_env);
		else if (flag_shell_var(name, EXPORT >> SHVAR_ADD_OFF, g_env)
			== FAILURE)
			set_shell_var(name, value, EXPORT, &g_env);
	}
	return (SUCCESS);
}
