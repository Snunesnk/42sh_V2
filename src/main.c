/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:27:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/28 15:38:31 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"
#include "builtins.h"
#include "quotes.h"

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
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	tmp = g_pending_cmd->next;
	free(g_pending_cmd->content);
	free(g_pending_cmd);
	g_pending_cmd = tmp;
	if (input[0] > 0)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", input);
		add_hentry(input, ft_strlen(input));
	}
	return (input);
}

int			exec_input(char *input, int fd)
{
	t_ast	*ast;
	t_list	*lst;
	int		status;
	char	*tmp;

	tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;
	lst = lexer(input);
	free(input);
	status = lst ? parser(lst, fd) : 2;
	if (status)
		return (main_error(status, lst));
	else if (((t_token*)(lst->content))->type == NEWLINE)
	{
		do_job_notification(g_first_job, NULL, NULL);
		free_lst(lst);
		return (g_retval);
	}
	ast = build_ast(&lst);
	g_retval = execute_node(ast, 1);
	g_trap = OFF;
	free_ast(ast);
	do_job_notification(g_first_job, NULL, NULL);
	return (g_retval);
}

int			exit_clean(int ret)
{
	extern char	**environ;
	t_list		*tmp;

	free_hash_table();
	ft_tabdel(&environ);
	ft_lstdel(&g_env, &del_env);
	ft_lstdel(&g_tmp_env, &del_env);
	ft_lstdel(&g_alias, &del_env);
	free_hist();
	while (g_pending_cmd)
	{
		tmp = g_pending_cmd->next;
		free(g_pending_cmd->content);
		free(g_pending_cmd);
		g_pending_cmd = tmp;
	}
	free(g_dis.prompt);
	exit(ret);
	return (ret);
}

static int	main_loop(int fd, int *status)
{
	char	*input;

	input = NULL;
	if (g_shell_is_interactive)
	{
		if (!g_pending_cmd && !(input = get_input_fd(fd, FULL_QUOTE, NULL)) \
				&& !g_pending_cmd)
			return (1);
		if (g_pending_cmd && input)
			free(input);
		if (g_pending_cmd)
			if (!(input = get_next_pending_cmd()))
				return (1);
	}
	else if (!(input = get_input_fd(fd, FULL_QUOTE, NULL)))
		return (1);
	*status = exec_input(input, fd);
	if (g_shell_is_interactive)
		test_hash_path();
	return (0);
}

int			main(int argc, char **argv)
{
	int	status;
	int	stop;

	stop = 0;
	status = 0;
	if (init_shell(argv[0], argc))
		return (EXIT_FAILURE);
	while (stop == 0)
	{
		if (g_onecmd)
			stop = 1;
		if (main_loop(STDIN_FILENO, &status))
			break ;
	}
	free_hist();
	return (exit_clean(status));
}
