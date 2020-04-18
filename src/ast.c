/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:04:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 12:12:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static t_list	*build_leaf(t_list **lst)
{
	t_list	*pipeline;
	t_list	*prev;

	pipeline = *lst;
	prev = *lst;
	while (((t_token*)((*lst)->content))->type != AND_IF
		&& ((t_token*)((*lst)->content))->type != OR_IF
		&& ((t_token*)((*lst)->content))->type != SEMI
		&& ((t_token*)((*lst)->content))->type != AND
		&& ((t_token*)((*lst)->content))->type != NEWLINE)
	{
		prev = *lst;
		*lst = (*lst)->next;
	}
	prev->next = NULL;
	return (pipeline);
}

static t_ast	*build_node(t_list **lst)
{
	t_list	*pipeline;
	t_list	*content;
	int		type;

	pipeline = build_leaf(lst);
	type = ((t_token*)((*lst)->content))->type;
	if (type == AND_IF || type == OR_IF)
	{
		content = (*lst);
		(*lst) = (*lst)->next;
		content->next = NULL;
		return (alloc_node(type, content,
			alloc_node(WORD, pipeline, NULL, NULL),
			build_node(lst)));
	}
	return (alloc_node(WORD, pipeline, NULL, NULL));
}

t_ast			*build_ast(t_list **lst)
{
	t_ast	*ast;
	t_list	*content;
	int		type;

	if (((t_token*)((*lst)->content))->type == NEWLINE)
	{
		free_lst(*lst);
		return (NULL);
	}
	ast = build_node(lst);
	if (((t_token*)((*lst)->content))->type == NEWLINE)
	{
		free_lst(*lst);
		return (ast);
	}
	type = ((t_token*)((*lst)->content))->type;
	if (type == SEMI || type == AND)
	{
		content = (*lst);
		(*lst) = (*lst)->next;
		content->next = NULL;
		ast = alloc_node(type, content, ast, build_ast(lst));
	}
	return (ast);
}
