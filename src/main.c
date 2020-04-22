/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:27:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/22 18:29:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"
#include "builtins.h"

t_list		*g_pending_cmd = NULL;
t_list		*g_env = NULL;
t_list		*g_tmp_env = NULL;
t_list		*g_alias = NULL;

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
		add_hentry(input, ft_strlen(input), 1);
	}
	return (input);
}

int			exec_input(char *input)
{
	t_ast	*ast;
	t_list	*lst;
	int		status;
	char	*tmp;

	status = 0;
	tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;
	lst = lexer(input);
	free(input);
	status = parser(lst);
	if (status || ((t_token*)(lst->content))->type == NEWLINE)
	{
		do_job_notification(g_first_job, NULL, NULL);
		free_lst(lst);
		return (status);
	}
	ast = build_ast(&lst);
	status = execute_node(ast, 1);
	free_ast(ast);
	g_retval = status;
	do_job_notification(g_first_job, NULL, NULL);
	return (status);
}

int			exit_clean(int ret)
{
	extern char	**environ;

	free_hash_table();
	ft_tabdel(&environ);
	ft_lstdel(&g_env, &del_env);
	ft_lstdel(&g_tmp_env, &del_env);
	ft_lstdel(&g_alias, &del_env);
	if (g_hist)
	{
		free(g_hist->history_content);
		free(g_hist);
		free(g_hist_loc);
	}
	free(g_dis.prompt);
	free_hash_table();
	exit(ret);
	return (ret);
}

int			main(int argc, char **argv)
{
	char			*input;
	volatile int	status;
	int				stop;
	char			*prompt;

	stop = 0;
	status = 0;
	if (init_shell(argv[0], argc))
		return (EXIT_FAILURE);
	while (stop == 0)
	{
		if (g_shell_is_interactive)
		{
			prompt = get_prompt();
			if (g_onecmd)
				stop = 1;
			if (!g_pending_cmd && !(input = ft_readline(prompt)))
				break ;
			else if (g_pending_cmd)
				if (!(input = get_next_pending_cmd()))
					break ;
		}
		else
		{
			if (get_stdin(&input) < 0)
				break;
		}
		exec_input(input);
		if (g_shell_is_interactive)
		{
			test_hash_path();
			free(prompt);
		}
	}
	free_hist();
	return (exit_clean(status));
}
