/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_char_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:03:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/11 13:09:29 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_char_tab(t_list *lst, char *(*f)(t_list *))
{
	char	**tab;
	char	*tmp;
	size_t	lst_len;
	size_t	i;

	if (lst == NULL || f == NULL)
		return (NULL);
	i = 0;
	lst_len = ft_lstlen(lst);
	tab = (char**)malloc(sizeof(char*) * (lst_len + 1));
	if (tab == NULL)
		return (NULL);
	while (lst != NULL)
	{
		tmp = f(lst);
		tab[i] = ft_strdup(tmp);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
