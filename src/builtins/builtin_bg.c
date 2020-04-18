/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 21:19:20 by yforeau          ###   ########.fr       */
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

	g_builtin_name = argv[0];
	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_background(j, 1);
	}
	else
		return (pbierror("usage: %s [job_spec]",
			g_builtin_name));
	return (0);
}
