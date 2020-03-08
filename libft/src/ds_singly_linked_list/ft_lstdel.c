/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:21:37 by efischer          #+#    #+#             */
/*   Updated: 2019/10/10 14:55:30 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (*alst != NULL && del != NULL)
	{
		while (*alst != NULL)
		{
			tmp = *alst;
			if ((*alst)->content)
				del((*alst)->content, (*alst)->content_size);
			*alst = tmp->next;
			free(tmp);
			tmp = NULL;
		}
	}
}
