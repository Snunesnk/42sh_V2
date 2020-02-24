/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/02/12 14:38:04 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include <readline/readline.h>

#include "libft.h"
#include "shell.h"
#include "error.h"

extern char	**environ;

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
	t_ast		*ast;
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
	while (21)
	{
		do_job_notification();
		if (!(input = readline("\e[38;5;44m21sh$ \e[0m")))
		{
			ft_printf("\nKICCCCCCKKKK OOOOOOFFFFFF\n\n");
			break;
		}
		update_status();
		ast = NULL;
		lexer(input, &ast);
/*		debug(lst);*/
//		debug_ast(ast);
		if (ast != NULL)
		{
			expansions(ast);
			if (parser(ast) == FAILURE)
				ft_putendl_fd("\nParse error", 2);
			else
			{
/*				ft_putendl("\nOK"); 
*/				ast_order(&ast);
		//		debug_ast(ast);
				status = execute_node(ast, 1); /* to capture */
			}
		}
/*		ft_lstdel(&lst, del);*/
		astdel(&ast);
		ft_strdel(&input);
		g_retval = status;
	}
	ft_tabdel(&environ);
	return (EXIT_SUCCESS);
}
