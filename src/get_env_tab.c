/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:23 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 14:36:31 by yforeau          ###   ########.fr       */
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
	size_t	i;

	if (lst == NULL || f == NULL)
		return (NULL);
	i = 0;
	buf = (char**)malloc(sizeof(char*) * (ft_lstlen(lst) + 1));
	if (buf == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if ((buf[i] = f(lst)))
			++i;
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
