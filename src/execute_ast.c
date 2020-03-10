/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/09 11:17:21 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

# define ASTERROR 125

int	execute_pipeline(t_ast *node, int foreground)
{
	return (execute_job(node->content, foreground));
}

int	execute_semi(t_ast *node, int foreground)
{
	if (node->left)
		execute_node(node->left, foreground);
	if (node->right)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_subshell(t_ast *node, int foreground)
{ /* Here is an idea for subshells */
	t_job	*j;
	pid_t	pid;
	int	status;

	if ((pid = fork()) == 0) /* If background, pid should be added to the job list
					Get the PID and add it to the list in case fg and ctrl + c */
	{
		pid = getpid();
		g_subshell = 1;
		restore_procmask();
		setpgid(pid, pid);
		exit(execute_node(node, foreground));
	}
	else if (pid < 0)
	{
		ft_printf("Fork subshell failed\n");
		exit(0);
	}
	if (foreground)
	{
		waitpid(pid, &status, WUNTRACED);
		return (get_exit_value(status));
	}
	else
	{
		j = (t_job*)ft_memalloc(sizeof(t_job));
		j->pgid = pid;
		j->first_process = (t_process*)ft_memalloc(sizeof(t_process));
		j->first_process->pid = pid;
		add_job_to_queue(j);
		return (0);
	}
}

int	execute_and(t_ast *node, int foreground)
{
	t_ast *lnode;

	lnode = node->left;
	if (lnode->type != NONE) /* Launch a subshell with node->left */
		execute_subshell(node->left, 0);
	else if (lnode->type == NONE)
		execute_node(node->left, 0);
	if (node->right)
		return (execute_node(node->right, foreground));
	return (0);
}

int	execute_andand(t_ast *node, int foreground)
{
	if (!execute_node(node->left, foreground))
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_or(t_ast *node, int foreground)
{
	if (execute_node(node->left, foreground))
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

/*int	execute_while(t_ast *node, int foreground)
{
	int	ret;

	ret = 1;
	while (!execute_node(node->left, foreground))
		ret = execute_node(node->right, foreground);
	return (ret);
}*/

/*
int	execute_if(t_ast *node)
{
	if (!execute_node(node->left))
		return (execute_node(node->right));
}
*/

int	execute_node(t_ast *node, int foreground)
{
	if (node->type == NONE)
		return (execute_pipeline(node, foreground));
	else if (node->type == SEMI)
		return (execute_semi(node, foreground));
	else if (node->type == AND)
		return (execute_and(node, foreground));
	else if (node->type == AND_IF)
		return (execute_andand(node, foreground));
	else if (node->type == OR_IF)
		return (execute_or(node, foreground));
/*	else if (node->type == WHILE_WORD)
		return (execute_while(node, foreground));*/
/*	else if (node->type == IF)
		return (execute_if(node));
*/
	return (ASTERROR);
}
