/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/18 15:03:27 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	cmd_echo(int argc, char **argv)
{
	--argc;
	++argv;
	while (argc > 0)
	{
		if (write(STDOUT_FILENO, argv[0], ft_strlen(argv[0])) == -1)
		{
			pbierror("write error: Bad file descriptor");
			return (1);
		}
		--argc;
		++argv;
		if (argc > 0)
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				pbierror("write error: Bad file descriptor");
				return (1);
			}
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
	{
		pbierror("write error: Bad file descriptor");
		return (1);
	}
	return (0);
}
