/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:22 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 13:20:01 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define ASTERROR 125

int	execute_and(t_ast *node, int foreground)
{
	t_ast *lnode;

	lnode = node->left;
	if (lnode->type != WORD)
		execute_subshell(node->left, 0);
	else if (lnode->type == WORD)
		execute_node(node->left, 0);
	if (node->right)
		return (execute_node(node->right, foreground));
	return (0);
}

int	execute_andand(t_ast *node, int foreground)
{
	int err;

	err = execute_node(node->left, foreground);
	if (err == SIGINT + 128)
		return (SIGINT + 128);
	else if (!err)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_or(t_ast *node, int foreground)
{
	int err;

	err = execute_node(node->left, foreground);
	if (err == SIGINT + 128)
		return (SIGINT + 128);
	else if (err)
		return (execute_node(node->right, foreground));
	return (ASTERROR);
}

int	execute_node(t_ast *node, int foreground)
{
	if (node->type == WORD)
		return (execute_pipeline(node, foreground));
	else if (node->type == SEMI)
		return (execute_semi(node, foreground));
	else if (node->type == AND)
		return (execute_and(node, foreground));
	else if (node->type == AND_IF)
		return (execute_andand(node, foreground));
	else if (node->type == OR_IF)
		return (execute_or(node, foreground));
	return (ASTERROR);
}
