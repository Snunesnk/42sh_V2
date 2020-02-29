/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:21:52 by efischer          #+#    #+#             */
/*   Updated: 2019/06/06 14:43:38 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	ft_split_lst(t_list **lst)
{
	t_list	*find_last_link;

	find_last_link = *lst;
	while (find_last_link->next != NULL)
	{
		find_last_link = find_last_link->next;
		if (find_last_link->next != NULL)
		{
			*lst = (*lst)->next;
			find_last_link = find_last_link->next;
		}
	}
}

t_list		*ft_merge_list(t_list *lst1, t_list *lst2, void sort(t_list**,
			t_list**, t_list**))
{
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	sort(&lst1, &lst2, &head);
	tmp = head;
	while (lst1 != NULL && lst2 != NULL)
	{
		sort(&lst1, &lst2, &tmp->next);
		tmp = tmp->next;
	}
	while (lst1 != NULL)
	{
		tmp->next = lst1;
		lst1 = lst1->next;
		tmp = tmp->next;
	}
	while (lst2 != NULL)
	{
		tmp->next = lst2;
		lst2 = lst2->next;
		tmp = tmp->next;
	}
	return (head);
}

void		ft_merge_sort(t_list **lst, void sort(t_list**, t_list**, t_list**))
{
	t_list	*lst1;
	t_list	*lst2;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	lst1 = *lst;
	ft_split_lst(lst);
	lst2 = (*lst)->next;
	(*lst)->next = NULL;
	ft_merge_sort(&lst1, sort);
	ft_merge_sort(&lst2, sort);
	*lst = ft_merge_list(lst1, lst2, sort);
}
