/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:39:25 by efischer          #+#    #+#             */
/*   Updated: 2020/03/09 14:59:12 by efischer         ###   ########.fr       */
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

static t_list	*remove_border(t_list **lst)
{
	t_list	*next;
	t_list	*tmp;

	next = (*lst)->next;
	ft_lstdelone(lst, &del);
	*lst = next;
	tmp = next;
	while (tmp != NULL && tmp->next != NULL && tmp->next->next != NULL && tmp->next->next->next != NULL)
		tmp = tmp->next;
	ft_lstdelone(&(tmp->next->next), &del);
	ft_lstdelone(&(tmp->next), &del);
	tmp->next = NULL;
	return (next);
}

static int		new_node_ast(t_ast **ast, t_list *head, t_list **lst)
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
	new_ast = astnew(NULL, ((t_token*)(process->content))->type);
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

int				build_ast(t_ast **ast, t_list *lst)
{
	t_list			*head;
	t_list			*tmp;
	enum e_token	type;

	head = remove_border(&lst);
	tmp = lst;
	while (head != NULL)
	{
		type = (lst == NULL) ? END : ((t_token*)(lst->content))->type;
		if (type == END || type == AND || type == AND_IF || type == OR_IF || type == SEMI)
		{
			if (lst == NULL)
				tmp = NULL;
			if (new_node_ast(ast, head, &tmp) == FAILURE)
				return (FAILURE);
			head = tmp;
			lst = head;
			tmp = lst;
			continue ;
		}
		lst = lst->next;
	}
	ast_order(ast);
	return (SUCCESS);
}
