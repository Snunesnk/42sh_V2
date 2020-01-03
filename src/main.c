/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2019/12/18 12:21:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "error.h"

extern char	**environ;

int			main(int argc, char **argv)
{
	int		index;
	uint64_t	buffer[BUF_SIZE];
	t_list		*lst;
	char		*input;
	volatile int	status;

	(void)argc;
	(void)argv;
	status = 0;
	g_progname = argv[0];
	if (init_shell())
		return (EXIT_FAILURE);
	if (!(environ = ft_tabcpy(environ)))
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	g_retval = e_success;
	if ((g_retval = set_minimal_env()))
	{
		psherror(g_retval, argv[0], e_cmd_type);
		ft_tabdel(&environ);
		return (1);
	}
	while (ft_printf("$> ") && get_stdin(&input) >= 0)
/*	if (ft_printf("$> ") && get_stdin(&input) >= 0) */ /* Debugg purpose */
	{
		lst = NULL;
		index = 0;
		ft_bzero(&buffer, sizeof(buffer));
		lexer(input, &lst);
		debug(lst);
		if (parser(lst, buffer, index) == EXIT_FAILURE)
			ft_putendl_fd("\nParse error", 2);
		else
		{
		/*	ft_putendl("\nOK"); */
			status = launch_all_jobs(lst); /* to capture */
		}
		ft_lstdel(&lst, del);
		ft_strdel(&input);
		g_retval = status;
	}
	ft_tabdel(&environ);
	return (EXIT_SUCCESS);
}
