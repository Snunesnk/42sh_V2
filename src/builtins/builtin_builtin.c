/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 13:50:06 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/28 13:55:23 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			cmd_builtin(int argc, char **argv)
{
	int	ret;

	(void)argc;
	ret = e_success;
	if (argv[1] && (ret = builtins_dispatcher(&argv[1])) != e_command_not_found)
		return (ret);
	else
		return (g_errordesc[psherror(e_no_builtin, argv[1], e_cmd_type)].code);
}
