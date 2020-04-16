/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:04:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 11:17:29 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
/*
t_ast			*semi_and(t_list **lst)
{
	t_ast	*node;
	int	type;

	node = node(SEMI, NULL, NULL, NULL); // Default node semi
	node->left = side(lst, &type); // Get the first pipeline or AND_IF or AND_OR etc. Type check if NEWLINE, SEMI or AND
	node->type = type; // Assign type of token ending node->left
	node->right = semi_and(lst); // Recursion to build right part of the ast
	return (node);
}
*/
static t_list		*build_leaf(t_list **lst, int *type)
{
	t_list	*pipeline;
	t_list	*prev;

	pipeline = *lst;
	prev = *lst;
	while (((t_token*)((*lst)->content))->type != AND_IF
		&& ((t_token*)((*lst)->content))->type != OR_IF
		&& ((t_token*)((*lst)->content))->type != SEMI
		&& ((t_token*)((*lst)->content))->type != NEWLINE)
	{
		prev = *lst;
		*lst = (*lst)->next;
	}
//	if (((t_token*)((*lst)->content))->type != AND_IF
//		|| ((t_token*)((*lst)->content))->type != OR_IF)
//		*type = ((t_token*)((*lst)->content))->type;
	if (((t_token*)((*lst)->content))->type == NEWLINE)
		*type = WORD;
//	*type = ((t_token*)((*lst)->content))->type;
	prev->next = NULL;
	return (pipeline);
}

static t_ast		*build_node(t_list **lst, int *type)
{
	t_ast	*node;
	t_list	*pipeline;

	pipeline = build_leaf(lst, type);
	node = alloc_node(*type, pipeline, NULL, NULL);
	return (node);
}

t_ast			*build_ast(t_list *lst)
{
	t_ast	*ast;
	int	type;

	ast = build_node(&lst, &type);
	return (ast);
}
