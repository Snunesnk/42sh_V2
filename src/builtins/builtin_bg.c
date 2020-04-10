/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 15:02:45 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/fg.html
*/

int	cmd_bg(int argc, char **argv)
{
	t_job	*j;

	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_background(j, 1);
	}
	else
		ft_dprintf(STDERR_FILENO, "bg: usage: bg [job_spec]\n");
	return (0);
}
