/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:43:13 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "error.h"

int		g_retval;
char		g_pwd[] = {0};
extern char	**environ;

static int	set_minimal_env(void)
{
	char	*tmp;
	int		shlvl;

	tmp = getcwd(NULL, 0);
	if (ft_setenv("PWD", tmp, 1))
		return (e_cannot_allocate_memory);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_getenv("SHLVL")))
	{
		if (ft_setenv("SHLVL", "1", 1))
			return (e_cannot_allocate_memory);
	}
	else
	{
		shlvl = ft_atoi(tmp) + 1;
		tmp = ft_itoa(shlvl);
		if (ft_setenv("SHLVL", tmp, 1))
			return (e_cannot_allocate_memory);
		ft_memdel((void**)&tmp);
	}
	if (PATH_MAX > 0)
	{
		tmp = ft_getenv("PWD");
		if (ft_strlen(tmp) <= PATH_MAX)
			ft_strcpy(g_pwd, ft_getenv("PWD"));
	}
	return (e_success);
}

static void	del(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}


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
