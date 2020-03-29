/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/12 18:19:00 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"
#include "builtins.h"

extern char	**environ;
t_list		*g_pending_cmd = NULL;
t_list		*g_env;
t_list		*g_alias;

char		*get_next_pending_cmd(void)
{
	char	*input;
	t_list	*tmp;

	if (!(input = ft_strdup((char *)g_pending_cmd->content)))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (NULL);
	}
	tmp = g_pending_cmd->next;
	free(g_pending_cmd->content);
	free(g_pending_cmd);
	g_pending_cmd = tmp;
	if (input[0] > 0)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", input);
		add_hentry(input, 1);
	}
	return (input);
}

int			exec_input(char *input)
{
	t_ast	*ast;
	int		status;

	if (input[0] <= 0)
	{
		free(input);
		return (0);
	}
	status = 0;
	ast = NULL;
	if (launch_lexer_parser(input, &ast) == SUCCESS)
	{
		debug_ast(ast);
	//	expansions(ast);
		status = execute_node(ast, 1); /* to capture */
	}
	astdel(&ast);
	ft_strdel(&input);
	g_retval = status;
	do_job_notification(first_job, NULL, NULL);
	return (status);
}

int			main(int argc, char **argv)
{
	char			*input;
	volatile int	status;

	(void)argc;
	status = 0;
	g_progname = argv[0];
	if (init_shell())
		return (EXIT_FAILURE);
	if (!(environ = ft_tabcpy(environ)))
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	init_hash_table();
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
		if (!g_pending_cmd && !(input = ft_readline("21sh$ ")))
		{
			ft_printf("\nKICCCCCCKKKK OOOOOOFFFFFF\n\n");
			break ;
		}
		else if (g_pending_cmd)
		{
			if (!(input = get_next_pending_cmd()))
				break ;
		}
		exec_input(input);
		test_hash_path();
	}
	free_hash_table();
	ft_tabdel(&environ);
/* Useless free functions, shell quits before in exit builtin */
	ft_lstdel(&g_env, &del_env);
	return (status);
}
