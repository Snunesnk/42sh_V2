/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:22:03 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/10 16:34:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

static void	*ft_memjoin(void *s1, void *s2, size_t len1, size_t len2)
{
	void				*dst;
	unsigned char		*tmp_dst;
	unsigned const char	*tmp_src;
	size_t				len;
	size_t				i;

	len = len1 + len2;
	dst = ft_memalloc(len);
	dst = ft_memcpy(dst, s1, len1);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned const char *)s2;
	i = len1;
	while (i < len)
		tmp_dst[i++] = *tmp_src++;
	return (tmp_dst);
}

static void	*get_str_to_print(ssize_t *len, t_list *lst,
			void (*f)(t_list*, t_list**))
{
	t_list	*elem;
	void	*str;
	void	*tmp;

	str = NULL;
	while (lst != NULL)
	{
		tmp = str;
		f(lst, &elem);
		if (elem == NULL)
			break ;
		str = ft_memjoin(tmp, elem->content, *len, elem->content_size);
		*len += elem->content_size;
		free(tmp);
		ft_strdel((char**)&elem->content);
		free(elem);
		lst = lst->next;
	}
	return (str);
}

int			ft_lstprint(t_list *lst, void (*f)(t_list*, t_list**))
{
	void	*str;
	ssize_t	len;

	len = 0;
	if (lst == NULL)
		return (SUCCESS);
	if (f == NULL)
		return (FAILURE);
	str = get_str_to_print(&len, lst, f);
	if (write(1, str, len) == FAILURE)
		len = FAILURE;
	free(str);
	return (len);
}
