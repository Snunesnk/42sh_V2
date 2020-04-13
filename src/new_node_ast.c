/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:41:14 by efischer          #+#    #+#             */
/*   Updated: 2020/04/13 12:27:06 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void		astadd_left(t_ast **ast, t_ast *new_ast)
{
	t_ast	*head;

	head = *ast;
	if (*ast == NULL)
		*ast = new_ast;
	else
	{
		while ((*ast)->left != NULL)
			*ast = (*ast)->right;
		(*ast)->left = new_ast;
		*ast = head;
	}
}

static void		astadd_right(t_ast **ast, t_ast *new_ast)
{
	t_ast	*head;

	head = *ast;
	if (*ast == NULL)
		*ast = new_ast;
	else
	{
		while ((*ast)->right != NULL)
			*ast = (*ast)->right;
		(*ast)->right = new_ast;
		*ast = head;
	}
}

static t_ast	*astnew(t_list *lst, uint64_t type)
{
	t_ast	*ast;

	ast = (t_ast*)malloc(sizeof(t_ast));
	if (ast != NULL)
	{
		ft_bzero(ast, sizeof(t_ast));
		ast->type = type;
		ast->content = lst;
	}
	return (ast);
}

int				new_node_ast(t_ast **ast, t_list *head, t_list **lst,
					int type)
{
	t_ast	*new_ast;
	t_list	*tmp;
	t_list	*process;

	if (*lst == NULL)
	{
		new_ast = astnew(head, NONE);
		astadd_right(ast, new_ast);
		return (SUCCESS);
	}
	process = (*lst)->next;
	if (process != NULL)
		tmp = process->next;
	new_ast = astnew(NULL, type);
	if (new_ast == NULL)
		return (FAILURE);
	(*lst)->next = NULL;
	astadd_right(ast, new_ast);
	*lst = tmp;
	ft_lstdelone(&process, &del);
	new_ast = astnew(head, NONE);
	if (new_ast == NULL)
		return (FAILURE);
	astadd_left(ast, new_ast);
	return (SUCCESS);
}
