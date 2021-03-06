/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:08 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/20 14:22:50 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	tab_remove_first_elem(int *ac, char ***av)
{
	if (*ac == 1)
		ft_free_tab(*ac, av);
	else
	{
		free(**av);
		ft_memmove(*av, *av + 1, *ac * sizeof(char *));
	}
	--(*ac);
}

static int	flags_shvar_cmp(uint64_t *flags, t_shell_var *svar)
{
	return ((svar->flag & *flags) != *flags);
}

void		unset_temp_shell_variables(void)
{
	uint64_t	flags;

	flags = TEMP;
	ft_lst_del_if(&g_env, (void *)&flags, del_env, flags_shvar_cmp);
	ft_lstaddend(&g_env, g_tmp_env);
	g_tmp_env = NULL;
	ft_merge_sort(&g_env, alpha_sort);
}

void		set_temp_shell_variables(void)
{
	t_list		*lst;
	t_shell_var	*svar;

	lst = g_env;
	while (lst)
	{
		svar = (t_shell_var *)lst->content;
		if (svar->flag & TEMP)
		{
			svar->flag &= ~TEMP;
			unset_shell_var(svar->name, &g_tmp_env);
		}
		lst = lst->next;
	}
}

int			treat_shell_variables(t_process *p, uint64_t flags)
{
	char			*name;
	char			*value;

	if (p->argc < 0 || !p->argv)
		return (FAILURE);
	else if (!p->argv[0] || !p->assignments_count)
		return (SUCCESS);
	while (p->argv && p->assignments_count)
	{
		if (get_assignment(p->argv[0], &name, &value) == FAILURE)
			return (FAILURE);
		*value++ = 0;
		if (set_shell_var(name, value, flags, &g_env) == FAILURE)
			return (FAILURE);
		tab_remove_first_elem(&p->argc, &p->argv);
		--p->assignments_count;
	}
	ft_merge_sort(&g_env, alpha_sort);
	return (SUCCESS);
}
