/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/11 11:22:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
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
	char			*input;
	volatile int	status;

	(void)argc;
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
		if (launch_lexer_parser(input, &ast) == SUCCESS)
		{
		//	expansions(ast);
			status = execute_node(ast, 1); /* to capture */
		}
		astdel(&ast);
		ft_strdel(&input);
		g_retval = status;
		do_job_notification(first_job, NULL, NULL);
	}
	free_hash_table();
	ft_tabdel(&environ);
/* Useless free functions, shell quits before in exit builtin */
	ft_lstdel(&g_env, &del_env);
	return (EXIT_SUCCESS);
}
