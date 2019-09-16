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

	i = 1;
	status = g_retval;
	if (argc > 1)
	{
		if (!ft_strcmp("--", argv[i]))
		{
			++i;
			if (argc == i)
			{
				ft_tabdel(&argv);
				ft_tabdel(&environ);
				write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
				exit(status);
			}
		}
		if (*argv[i]
			&& (((*argv[i] == '-' || *argv[i] == '+') && ft_str_is_numeric(&argv[i][i]))
			|| ft_str_is_numeric(argv[i])) && ft_strcmp("--", argv[i]))
		{
			write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
			if (argc > i + 1)
			{
				ft_dprintf(STDERR_FILENO,
				"%s: %s: too many arguments\n",	g_progname, argv[0]);
				return (1);
			}
			status = (unsigned char)ft_atoi(argv[i]);
			ft_tabdel(&argv);
			ft_tabdel(&environ);
			exit(status);
		}
		else
		{
			write(STDOUT_FILENO, "exit\n", 5 * sizeof(char));
			ft_dprintf(STDERR_FILENO,
			"%s: %s: %s: numeric argument required\n",
					g_progname, argv[0], argv[i]);
			ft_tabdel(&argv);
			ft_tabdel(&environ);
			exit(2);
		}
	}
	ft_tabdel(&argv);
	ft_tabdel(&environ);
	exit(status);
}
