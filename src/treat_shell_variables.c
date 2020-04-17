/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:08 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/17 12:16:34 by yforeau          ###   ########.fr       */
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

int			treat_shell_variables(t_process *p, uint64_t flags)
{
	char			*name;
	char			*value;

	if (!p->argv[0])
		return (SUCCESS);
	while (p->argv && get_assignment(p->argv[0], &name, &value) == SUCCESS)
	{
		*value++ = 0;
		if (set_shell_var_value(name, value, flags, &g_env) == FAILURE)
			return (FAILURE);
		tab_remove_first_elem(&p->argc, &p->argv);
	}
	ft_merge_sort(&g_env, alpha_sort);
	return (SUCCESS);
}
