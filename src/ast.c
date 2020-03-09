/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:39:25 by efischer          #+#    #+#             */
/*   Updated: 2020/02/12 13:12:01 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*static void		astadd_left(t_ast **ast, t_ast *new_ast)
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
}*/

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

static void		remove_border(t_list **head, t_list **lst)
{
	*head = (*lst)->next;
	ft_lstdelone(lst, &del);
	*lst = *head;
}

/*static int		new_node_ast(t_ast **ast, t_list *head, t_list **lst)
{
	t_ast	*new_ast;
	t_list	*tmp;

	tmp = (*lst)->next;
	new_ast = astnew(NULL, ((t_token*)((*lst)->content))->type);
	if (new_ast == NULL)
		return (FAILURE);
	astadd_right(ast, new_ast);
	ft_lstdelone(lst, &del);
	new_ast = astnew(head, NONE);
	if (new_ast == NULL)
		return (FAILURE);
	astadd_left(ast, new_ast);
	*lst = tmp;
	return (SUCCESS);
}*/

int				build_ast(t_ast **ast, t_list *lst)
{
	t_ast		*new_ast;
	t_list		*head;
	t_list		*tmp;
	uint64_t	type;
	int			ret;

	ret = SUCCESS;
	head = lst;
	tmp = lst;
	while (lst != NULL)
	{
		ft_putendl("Im here");
		type = ((t_token*)(lst->content))->type;
		if (type == START)
			remove_border(&head, &lst);
		if (type == END)
		{
			tmp->next = NULL;
			ft_lstdelone(&lst, &del);
		}
		else	
		{
			/*if (type == AND || type == AND_IF || type == OR_IF || type == SEMI)
			{
				ret = new_node_ast(ast, head, &lst);
				if (ret == FAILURE)
					return (ret);
				head = lst;
			}*/
			if (lst != NULL)
			{
				tmp = lst;
				lst = lst->next;
			}
		}
		ft_printf("head: %p\n", head);
	}
	if (head != NULL)
	{
		new_ast = astnew(head, NONE);
		astadd_right(ast, new_ast);
	}
	ast_order(ast);
	return (ret);
}
