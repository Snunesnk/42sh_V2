/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/09 13:21:47 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "ft_readline.h"

extern char	**environ;
t_list		*g_env;

void	astdel(t_ast **ast)
{
	if (*ast != NULL)
	{
		ft_lstdel(&(*ast)->content, del);
		if ((*ast)->left != NULL)
			astdel((t_ast**)&(*ast)->left);
		if ((*ast)->right != NULL)
			astdel((t_ast**)&(*ast)->right);
		free(*ast);
		*ast = NULL;
	}
}

int			main(int argc, char **argv)
{
	t_ast			*ast;
	t_list			*lst;
	char			*input;
	volatile int	status;

	(void)argc;
	(void)argv;
	status = 0;
	g_progname = argv[0];
	if (init_shell())
		return (EXIT_FAILURE);
	if (!(g_hash_table = ft_memalloc(sizeof(*g_hash_table) * HASH_SIZE)))
		return (EXIT_FAILURE);
	if (!(environ = ft_tabcpy(environ)))
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	get_env_list(environ);
//	ft_lstprint(g_env, &print_env);
	g_retval = e_success;
	if ((g_retval = set_minimal_env()))
	{
		psherror(g_retval, argv[0], e_cmd_type);
		ft_tabdel(&environ);
		return (1);
	}
	while (21)
	{
		if (!(input = ft_readline("21sh$ ")))
		{
			ft_printf("\nKICCCCCCKKKK OOOOOOFFFFFF\n\n");
			break ;
		}
		ast = NULL;
		lst = NULL;
		lexer(input, &lst);
		if (lst != NULL)
		{
		//	expansions(ast);
			debug(lst);
			if (parser(lst) != FAILURE)
			{
				build_ast(&ast, lst);
				debug_ast(ast);
			//	status = execute_node(ast, 1); /* to capture */
			}
		}
/*		ft_lstdel(&lst, del);*/
		astdel(&ast);
		ft_strdel(&input);
		g_retval = status;
		do_job_notification();
	}
	free_hash_table();
	ft_tabdel(&environ);
/* Useless free functions, shell quits before in exit builtin */
	ft_lstdel(&g_env, &del_env);
	return (EXIT_SUCCESS);
}
