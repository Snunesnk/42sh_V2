/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/05 16:15:40 by yforeau          ###   ########.fr       */
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
	if (node->right)
	{
		execute_node(node->left, foreground);
		return (execute_node(node->right, foreground));
	}
	else
		return (execute_node(node->left, foreground));
}

static int	parent_shell(pid_t pid)
{
	t_job	*j;

	j = (t_job*)ft_memalloc(sizeof(t_job));
	j->pgid = pid;
	j->first_process = (t_process*)ft_memalloc(sizeof(t_process));
	j->first_process->pid = pid;
	j->pgid = pid;
	j->command = ft_strdup("subshell"); /* Should be infix to concatenate elements of command */
	add_job_to_queue(j);
//	ft_printf("Parent shellpid: %d, job:%d\n", g_shell_pgid, pid);
//	printjob();
	return (0);
}

int			execute_subshell(t_ast *node, int foreground)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		/* Set off job control in subshell */
		g_job_control_enabled = OFF;
		g_shell_is_interactive = OFF;
		/* Reset job list in subshell */
		free_all_jobs();
		/* Reset signal masks */
		restore_procmask();
		/* Get pid of process */
		pid = getpid();
//		ft_printf("Fork subshell: pid: %d\n", pid);
		g_shell_pgid = pid;
		if (setpgid(pid, g_shell_pgid))
			exit_clean(1);
		/* Continue normal execution of remaining AST */
		exit_clean(execute_node(node, foreground));
	}
	else if (pid < 0)
	{
		ft_printf("Fork subshell failed\n");
		exit_clean(0);
	}
	return (parent_shell(pid));
}
