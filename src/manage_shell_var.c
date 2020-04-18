/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 01:53:59 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int				name_shvar_cmp(void *str_ref, void *shvar_ptr)
{
	char	*name;

	name = ((t_shell_var *)shvar_ptr)->name;
	return (ft_strcmp((char *)str_ref, name));
}

int				unset_shell_var(const char *name, t_list **svar_lst)
{
	if (!ft_lst_del_if(svar_lst, (void *)name, del_env, name_shvar_cmp))
		return (FAILURE);
	return (SUCCESS);
}

char			*get_shell_var(const char *name, t_list *svar_lst)
{
	t_list	*elem;

	if (!(elem = ft_lst_find(svar_lst, (void *)name, name_shvar_cmp)))
		return (NULL);
	return (((t_shell_var *)elem->content)->value);
}
