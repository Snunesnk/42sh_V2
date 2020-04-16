/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 17:44:00 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int				set_shell_var(t_list *elem, char *name,
					char *value, uint64_t flags)
{
	t_list			*lst_new;
	t_shell_var		shell_var;

	ft_bzero(&shell_var, sizeof(shell_var));
	if (!elem || (flags & TEMP))
	{
		shell_var.name = name;
		shell_var.flag = elem ? ((t_shell_var *)elem->content)->flag : flags;
		shell_var.value = elem ? ((t_shell_var *)elem->content)->value : value;
		lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
		if (lst_new == NULL)
			return (FAILURE);
		ft_lstadd(elem ? &g_tmp_env : &g_env, lst_new);
	}
	if (elem)
	{
		if (!(flags & TEMP))
			ft_strdel(&((t_shell_var *)(elem->content))->value);
		((t_shell_var*)(elem->content))->value = value;
		((t_shell_var*)(elem->content))->flag |= flags; //TODO: change to '='
	}
	return (SUCCESS);
}

int				set_shell_var_value(char *name, char *value,
					uint64_t flags, t_list *svar_lst)
{
	t_list	*elem;

	elem = get_shell_var(name, svar_lst);
	return (set_shell_var(elem, name, value, flags));
}

t_list			*get_shell_var(char *name, t_list *svar_lst)
{
	while (svar_lst)
	{
		if (ft_strequ(name, ((t_shell_var*)(svar_lst->content))->name))
			break ;
		svar_lst = svar_lst->next;
	}
	return (svar_lst);
}

char			*get_shell_var_value(char *name, t_list *svar_lst)
{
	t_list	*elem;

	if (!(elem = get_shell_var(name, svar_lst)))
		return (NULL);
	return (((t_shell_var *)elem->content)->value);
}
