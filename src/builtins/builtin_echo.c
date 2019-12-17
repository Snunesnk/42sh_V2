/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:13:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "job_control.h"

int	cmd_echo(int argc, t_process *p)
{
	int	i;

	(void)argc;
	i = 1;
	while (p->argv[i])
	{
		if (p->argv[i + 1])
		{
			ft_dprintf(p->outfile, "%s ", p->argv[i]);
		}
		else
		{
			ft_dprintf(p->outfile, "%s\n", p->argv[i]);
		}
		++i;
	}
	return (0);
}
