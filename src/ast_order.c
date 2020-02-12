/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:00:22 by efischer          #+#    #+#             */
/*   Updated: 2020/02/12 11:17:05 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	node_rot(t_ast **ast, t_ast *prev_node, t_ast **head)
{
	t_ast	*tmp;

	if (prev_node == NULL)
	{
		tmp = (*ast)->right;
		(*head)->right = ((t_ast*)(tmp))->left;
		((t_ast*)(tmp))->left = (*head);
		(*head) = tmp;
	}
	else
	{
		tmp = *ast;
		prev_node->right = (*ast)->right;
		tmp->right = ((t_ast*)(prev_node->right))->left;
		((t_ast*)(prev_node->right))->left = tmp;
	}
}

static void	check_order(t_ast **ast, t_ast **prev_node, t_ast **head)
{
	if ((*ast)->type == AND_IF || (*ast)->type == OR_IF)
	{
		if (((t_ast*)((*ast)->right))->type == AND)
		{
			node_rot(ast, *prev_node, head);
			*ast = *head;
			*prev_node = NULL;
		}
		else
		{
			*prev_node = *ast;
			*ast = (*ast)->right;
		}
	}
	else
	{
		*prev_node = *ast;
		*ast = (*ast)->right;
	}
}

void		ast_order(t_ast **ast)
{
	t_ast	*head;
	t_ast	*prev_node;

	head = *ast;
	prev_node = NULL;
	if (*ast != NULL)
	{
		while ((*ast)->right)
			check_order(ast, &prev_node, &head);
	}
	*ast = head;
}
