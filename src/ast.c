/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:39:25 by efischer          #+#    #+#             */
/*   Updated: 2020/04/13 12:23:48 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static t_list	*remove_border(t_list **lst)
{
	t_list	*next;
	t_list	*tmp;

	next = (*lst)->next;
	ft_lstdelone(lst, &del);
	*lst = next;
	tmp = next;
	while (tmp != NULL && tmp->next != NULL && tmp->next->next != NULL
		&& tmp->next->next->next != NULL)
	{
		tmp = tmp->next;
	}
	ft_lstdelone(&(tmp->next->next), &del);
	ft_lstdelone(&(tmp->next), &del);
	tmp->next = NULL;
	return (next);
}

int				build_ast(t_ast **ast, t_list *lst)
{
	t_list	*head;
	t_list	*tmp;
	int		type;

	head = remove_border(&lst);
	tmp = lst;
	while (head)
	{
		type = lst ? ((t_token*)(lst->content))->type : END;
		if (type == END || type == AND || type == AND_IF
			|| type == OR_IF || type == SEMI)
		{
			if (!lst)
				tmp = NULL;
			if (new_node_ast(ast, head, &tmp, type) == FAILURE)
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
