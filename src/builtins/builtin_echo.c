/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/14 18:56:57 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	cmd_echo(int argc, char **argv)
{
	--argc;
	++argv;
	while (argc > 0)
	{
		ft_printf("%s", argv[0]);
		--argc;
		++argv;
		if (argc > 0)
			ft_printf(" ");
	}
	ft_printf("\n");
	return (0);
}
