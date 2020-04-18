/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 01:58:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				cmd_unsetenv(int argc, char **argv)
{
	if (argc != 2)
	{
		psherror(e_invalid_input, argv[0], e_cmd_type);
		ft_dprintf(STDERR_FILENO, "Usage: %s VAR [VALUE]\n", argv[0]);
		return (g_errordesc[e_invalid_input].code);
	}
	else if (!argv[1] || !*argv[1] || ft_strstr(argv[1], "="))
	{
		g_errno = E_EINVAL;
		ft_perror(NULL);
		return (FAILURE);
	}
	else
		flag_shell_var(argv[1], EXPORT >> SHVAR_RM_OFF, g_env);
	return (SUCCESS);
}
