/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 08:23:00 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int				cmd_unsetenv(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc == 1)
	{
		pbierror("usage: %s name ...", g_builtin_name);
		ret = 1;
	}
	while (*++argv)
	{
		if (!**argv || ft_strchr(*argv, '='))
		{
			pbierror("'%s': not a valid identifier", *argv);
			ret = 1;
		}
		else
			flag_shell_var(*argv, EXPORT >> SHVAR_RM_OFF, g_env);
	}
	return (ret);
}
