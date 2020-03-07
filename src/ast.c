/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:39:25 by efischer          #+#    #+#             */
/*   Updated: 2020/03/07 16:56:50 by snunes           ###   ########.fr       */
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

int				build_ast(uint64_t type, t_ast **ast, t_list *lst)
{
	t_ast	*new_ast;
	int		ret;

	ret = SUCCESS;
	if (type == AND || type == AND_IF || type == OR_IF || type == SEMI)
	{
		new_ast = astnew(NULL, type);
		astadd_right(ast, new_ast);
		new_ast = astnew(lst, NONE);
		astadd_left(ast, new_ast);
	}
	else
	{
		new_ast = astnew(lst, NONE);
		astadd_right(ast, new_ast);
	}
	if (new_ast == NULL)
		ret = FAILURE;
	return (ret);
}
