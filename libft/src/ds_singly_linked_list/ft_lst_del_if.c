/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:02:12 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/16 13:02:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_del_if(t_list **lst, void *content_ref,
			void (*del)(void *, size_t), int (*cmp)())
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	if (!lst || !*lst || !del || !cmp)
		return ;
	prev = NULL;
	cur = *lst;
	next = cur ? cur->next : NULL;
	while (cur)
	{
		if (!cmp(content_ref, cur->content))
		{
			ft_lstdelone(&cur, del);
			if (prev)
				prev->next = next;
			else
				*lst = next;
		}
		prev = cur ? cur : prev;
		cur = next;
		next = cur ? cur->next : next;
	}
}
