/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:04:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 13:07:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static t_list		*build_leaf(t_list **lst)
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

static t_ast		*build_node(t_list **lst)
{
	t_list	*pipeline;
	int		type;

	pipeline = build_leaf(lst);
//	debug(*lst);
	type = ((t_token*)((*lst)->content))->type;
	if (type  == AND_IF || type  == OR_IF)
	{
		(*lst) = (*lst)->next;
//		ft_printf("\n|%s|\n", g_tokval[type]);
		return (alloc_node(type, NULL,
			alloc_node(WORD, pipeline, NULL, NULL),
			build_node(lst)));
	}
	return (alloc_node(WORD, pipeline, NULL, NULL));
}

t_ast			*build_ast(t_list **lst)
{
	t_ast	*ast;
	int		type;

	if (((t_token*)((*lst)->content))->type == NEWLINE)
		return (NULL);
	ast = build_node(lst);
//	ft_printf("\n--START---\n");
//	debug_ast(ast);
//	ft_printf("\n--END---\n");
	type = ((t_token*)((*lst)->content))->type;
//	ft_printf("\n|%s|\n", g_tokval[type]);
	if (type == SEMI || type == AND)
	{
		(*lst) = (*lst)->next;
		ast = alloc_node(type, NULL, ast, build_ast(lst));
	}
	return (ast);
}
