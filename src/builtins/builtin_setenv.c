/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 08:21:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int			cmd_setenv(int argc, char **argv)
{
	char	*name;
	char	*value;

	if (argc == 1)
	{
		pbierror("usage: %s name[=value] ...", g_builtin_name);
		return (1);
	}
	while (*++argv)
	{
		if (get_assignment(*argv, &name, &value) == SUCCESS)
			*value++ = 0;
		if (!*name || *name == '=')
			pbierror("`%s': not a valid identifier", name);
		else if (value)
			set_shell_var(name, value, EXPORT >> SHVAR_ADD_OFF, &g_env);
		else if (flag_shell_var(name, EXPORT >> SHVAR_ADD_OFF, g_env)
			== FAILURE)
			set_shell_var(name, value, EXPORT, &g_env);
	}
	return (0);
}
