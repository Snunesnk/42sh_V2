/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 18:19:12 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/17 21:07:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static uint64_t	set_flags(uint64_t old_flags, uint64_t new_flags)
{
	uint64_t	flags_to_add;
	uint64_t	flags_to_remove;

	flags_to_add = new_flags & SHVAR_ADD_MASK;
	flags_to_remove = new_flags & SHVAR_RM_MASK;
	if (flags_to_add || flags_to_remove)
	{
		old_flags |= flags_to_add << SHVAR_ADD_OFF;
		old_flags &= ~(flags_to_remove << SHVAR_RM_OFF);
		return (old_flags);
	}
	else
		return (new_flags & SHVAR_OVERWRITE_MASK);
}

static int		set_shell_var_internal(t_shell_var *orig_var,
					t_shell_var *new_var, t_list **svar_lst)
{
	int		flag;
	t_list	*new_elem;

	flag = new_var->flag;
	if (orig_var)
	{
		ft_swap_p((uintptr_t *)&orig_var->name, (uintptr_t *)&new_var->name);
		ft_swap_p((uintptr_t *)&orig_var->value, (uintptr_t *)&new_var->value);
		orig_var->flag = set_flags(orig_var->flag, flag);
	}
	else
	{
		new_var->flag = set_flags(0, flag);
		if (!(new_elem = ft_lstnew(new_var, sizeof(t_shell_var))))
			return (FAILURE);
		else
			ft_lstadd(svar_lst, new_elem);
	}
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
