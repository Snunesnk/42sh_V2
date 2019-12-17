/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:22:00 by efischer          #+#    #+#             */
/*   Updated: 2019/06/06 15:22:01 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_str(char const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	list->content_size = 0;
	list->next = NULL;
	if (content == NULL)
		list->content = NULL;
	else
	{
		if (!(list->content = ft_strdup(content)))
		{
			free(list);
			list = NULL;
		}
		else
			list->content_size = content_size;
	}
	return (list);
}
