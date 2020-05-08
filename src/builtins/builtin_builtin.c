/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 09:13:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/08 09:29:02 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int		cmd_builtin(int argc, char **argv)
{
	int err;

	if (argc >= 2)
	{
		err = builtins_dispatcher(&argv[1]);
		if (err == e_no_builtin)
		{
			psherror(e_no_builtin, argv[1], e_cmd_type);
			return (g_errordesc[err].code);
		}
		return (err);
	}
	return (0);
}
