/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:32:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 19:22:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "libft.h"
#include "shell_variables.h"
#include "sig_handler.h"
#include "builtins.h"
#include "prompt.h"
#include "input.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "path.h"

int		g_retval;
char	g_pwd[] = {0};
extern char	**environ;
extern int	g_fd_prompt;

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

static char	*tab_to_str(char **av)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	while (av[i] != NULL)
	{
		str = ft_join_free(str, av[i], 1);
		if (str == NULL)
			break ;
		i++;
	}
	return (str);
}

int		main(int argc, char **argv)
{
	volatile int	status;
	t_list		*lst;
	char		*input;

	(void)argc;
	status = 0;
	g_progname = argv[0];
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
	set_signals(0);
	if ((g_fd_prompt = initialize_prompt_fd()) == -1)
	{
		ft_tabdel(&environ);
		return (2);
	}
	if (init_shell())
		return (EXIT_FAILURE);
	while (prompt_display(g_retval) && get_stdin(&input) >= 0)
	{
		lexer(input, &lst);
		free(input);
		debug(lst);
		if (parser(lst) == FAILURE)
			ft_putendl_fd("\nParse error", 2);
		else
		{
			ft_putendl("\nOK");
			status = launch_all_jobs(lst); /* to capture */
		}
		ft_lstdel(&lst, del);
	}
	ft_tabdel(&environ);
	free_all_shvar();
	return (0);
}
