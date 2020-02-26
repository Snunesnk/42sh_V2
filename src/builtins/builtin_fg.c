/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/fg.html
*/

int	cmd_fg(int argc, char **argv)
{
	t_job	*j;

	if (argc == 2)
	{
		j = find_job(ft_atoi(argv[1]));
		put_job_in_foreground(j, 1);
	}
//	else if (argc > 2)
//	{
//		if (argv[1][0] == '-')
//			ft_dprintf(STDERR_FILENO, "fg: -l: invalid option\n");
	else
		ft_dprintf(STDERR_FILENO, "fg: usage: fg [job_spec]\n");
//	}
		
	return (0);
}
