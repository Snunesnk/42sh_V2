/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/26 13:21:06 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

/*
**  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/fg.html
*/

int	cmd_bg(int argc, char **argv)
{
	t_job	*j;

	if (!g_shell_is_interactive)
		return (g_errordesc[psherror(e_no_job_control, argv[0], e_cmd_type)].code);
	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_background(j, 1);
	}
	else
	{
		return (pbierror("usage: %s [job_spec]",
					g_builtin_name));
	}
	return (0);
}
