/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:31:52 by efischer          #+#    #+#             */
/*   Updated: 2020/03/05 11:32:10 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*get_env_elem(t_list *lst)
{
	char	*elem;

	elem = NULL;
	if ((((t_shell_var*)(lst->content))->flag & EXPORT) == EXPORT
			&& (((t_shell_var*)(lst->content))->flag & SET) == SET)
	{
		ft_asprintf(&elem, "%s=%s", ((t_shell_var*)(lst->content))->name,
				((t_shell_var*)(lst->content))->value);
	}
	return (elem);
}

char	**ft_lst_to_char_tab(t_list *lst, char *(*f)(t_list *))
{
	char	**buf;
	char	*tmp;
	size_t	lst_len;
	size_t	i;

	if (lst == NULL || f == NULL)
		return (NULL);
	i = 0;
	lst_len = ft_lstlen(lst);
	buf = (char**)malloc(sizeof(char*) * (lst_len + 1));
	if (buf == NULL)
		return (NULL);
	while (lst != NULL)
	{
		tmp = f(lst);
		if (tmp != NULL)
		{
			buf[i] = ft_strdup(tmp);
			i++;
		}
		lst = lst->next;
	}
	buf[i] = NULL;
	return (buf);
}

char	**get_env_tab(void)
{
	extern t_list	*g_env;
	char			**buf;

	buf = ft_lst_to_char_tab(g_env, &get_env_elem);
	return (buf);
}
