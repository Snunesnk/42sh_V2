/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:14:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "jcont.h"

int	cmd_exit(int argc, char **argv)
{
	extern char	**environ;
	unsigned char	status;
	int		i;

	status = g_retval;
	if (argc > 3)
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: too many arguments\n",	g_progname, argv[0]);
		return (2);
	}
	if (argc == 2)
		i = 1;
	if (argc == 3)
	{
		if (ft_strcmp(argv[1], "--"))
		{
			ft_dprintf(STDERR_FILENO,
			"%s: %s: %s: numeric argument required\n",
					g_progname, argv[0], argv[1]);
			ft_tabdel(&argv);
			ft_tabdel(&environ);
			exit (2);
		}
		i = 2;
	}
	if (argc > 1)
	{
		if (*argv[i]
			&& (((*argv[i] == '-' || *argv[i] == '+') && ft_str_is_numeric(&argv[i][i]))
			|| ft_str_is_numeric(argv[i])))
				status = (unsigned char)ft_atoi(argv[i]);
		else
		{
			ft_dprintf(STDERR_FILENO,
			"%s: %s: %s: numeric argument required\n",
					g_progname, argv[0], argv[i]);
			return (2);
		}
	}
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(status);
}
