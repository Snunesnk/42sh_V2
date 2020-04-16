/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:27:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 13:44:00 by abarthel         ###   ########.fr       */
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
	t_list	*lst;
	int		status;

	status = 0;
	lst = lexer(input);
	free(input);
	status = parser(lst);
	if (status)
	{
		ft_lstdelone(&lst, &del);
		return (status);
	}
	ast = build_ast(&lst); /* Debugging AST */
//	debug_ast(ast);
	status = execute_node(ast, 1);
	astdel(&ast);
	g_retval = status;
	do_job_notification(g_first_job, NULL, NULL);
	return (status);
}

int			main(int argc, char **argv)
{
	char			*input;
	volatile int	status;
	int				stop;
	char			*prompt;

	stop = 0;
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
	g_retval = e_success;
	if ((g_retval = set_minimal_env()))
	{
		psherror(g_retval, argv[0], e_cmd_type);
		ft_tabdel(&environ);
		return (1);
	}
	while (stop == 0)
	{
		prompt = get_prompt();
		if (g_onecmd)
			stop = 1;
		if (!g_pending_cmd && !(input = ft_readline(prompt)))
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
		free(prompt);
	}
	free_hash_table();
	ft_tabdel(&environ);
	ft_lstdel(&g_env, &del_env);
	return (status);
}
