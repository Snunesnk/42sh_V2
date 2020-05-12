/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/12 17:45:12 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

#define ASTERROR 125

int			execute_pipeline(t_ast *node, int foreground)
{
	return (execute_job(node->content, foreground));
}

int			execute_semi(t_ast *node, int foreground)
{
	int err;

	if (node->right)
	{
		err = execute_node(node->left, foreground);
		if (err != SIGINT + 128)
			return (execute_node(node->right, foreground));
		else
			return (SIGINT + 128);
	}
	else
		return (execute_node(node->left, foreground));
}

static int	parent_shell(pid_t pid, t_ast *node)
{
	t_job	*j;

	j = (t_job*)ft_memalloc(sizeof(t_job));
	j->pgid = pid;
	j->first_process = (t_process*)ft_memalloc(sizeof(t_process));
	j->first_process->pid = pid;
	j->pgid = pid;
	get_job_command(node, &j->command);
	add_job_to_queue(j);
	format_job_info(j, "Launched");
	return (0);
}

int			execute_subshell(t_ast *node, int foreground)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		g_job_control_enabled = OFF;
		g_shell_is_interactive = OFF;
		free_all_jobs();
		restore_procmask();
		pid = getpid();
		g_shell_pgid = pid;
		if (setpgid(pid, g_shell_pgid))
			exit_clean(1);
		exit_clean(execute_node(node, foreground));
	}
	else if (pid < 0)
	{
		ft_printf("Fork subshell failed\n");
		exit_clean(0);
	}
	return (parent_shell(pid, node));
}
