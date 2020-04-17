/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/17 13:48:33 by yforeau          ###   ########.fr       */
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

static int		set_shell_var_internal(t_shell_var *orig_var,
					t_shell_var *new_var, t_list **svar_lst)
{
	int		flag;
	t_list	*new_elem;

	if (orig_var)
	{
		ft_swap_p((uintptr_t *)&orig_var->name, (uintptr_t *)&new_var->name);
		ft_swap_p((uintptr_t *)&orig_var->value, (uintptr_t *)&new_var->value);
		flag = new_var->flag;
		new_var->flag = orig_var->flag;
		orig_var->flag = flag;
	}
	else if (!(new_elem = ft_lstnew(new_var, sizeof(t_shell_var))))
		return (FAILURE);
	else
		ft_lstadd(svar_lst, new_elem);
	if (orig_var && !(flag & TEMP))
	{
		ft_strdel(&new_var->name);
		ft_strdel(&new_var->value);
	}
	return (SUCCESS);
}

int				set_shell_var(const char *name, const char *value,
					uint64_t flags, t_list **svar_lst)
{
	int			ret;
	t_list		*elem;
	t_shell_var	new_var;
	t_shell_var	*orig_var;

	ret = SUCCESS;
	elem = ft_lst_find(*svar_lst, (void *)name, name_shvar_cmp);
	orig_var = elem ? (t_shell_var *)elem->content : NULL;
	ft_bzero(&new_var, sizeof(t_shell_var));
	new_var.flag = flags;
	if (!(new_var.name = ft_strdup(name))
		|| (value && !(new_var.value = ft_strdup(value))))
		ret = FAILURE;
	if (ret == SUCCESS && orig_var && (flags & TEMP))
		ret = set_shell_var_internal(NULL, orig_var, &g_tmp_env);
	if (ret == SUCCESS)
		ret = set_shell_var_internal(orig_var, &new_var, svar_lst);
	if (ret == FAILURE)
	{
		ft_strdel(&new_var.name);
		ft_strdel(&new_var.value);
	}
	return (ret);
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
