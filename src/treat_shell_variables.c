/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:08 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 14:37:19 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char	**tab_remove_first_elem(int *ac, char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = NULL;
	if (*ac > 1)
	{
		new_tab = (char**)malloc(sizeof(char*) * *ac);
		if (new_tab == NULL)
			return (NULL);
		while (i + 1 < *ac)
		{
			new_tab[i] = ft_strdup(av[i + 1]);
			i++;
		}
		new_tab[i] = NULL;
	}
	ft_free_tab(*ac, &av);
	(*ac)--;
	return (new_tab);
}

static int	cmp_flags(uint64_t *flags, t_shell_var *svar)
{
	return ((svar->flag & *flags) != *flags);
}

void		unset_temp_shell_variables(void)
{
	uint64_t	flags;

	flags = TEMP;
	ft_lst_del_if(&g_env, (void *)&flags, del, cmp_flags);
	ft_lstaddend(&g_env, g_tmp_env);
	g_tmp_env = NULL;
	ft_merge_sort(&g_env, alpha_sort);
}

int			set_shell_var(t_list *elem, char *name,
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
		((t_shell_var*)(elem->content))->value = value;
		((t_shell_var*)(elem->content))->flag |= flags;
	}
	return (SUCCESS);
}

int			treat_shell_variables(t_process *p, uint64_t flags)
{
	t_list			*elem;
	char			*name;
	char			*value;

	if (!p->argv[0])
		return (0);
	while (p->argv != NULL && (value = is_valid_assignment(p->argv[0])))
	{
		name = ft_strndup(p->argv[0], value - p->argv[0]);
		value = ft_strdup(value + 1);
		elem = get_shell_var(name, g_env);
		if (!name || !value
			|| set_shell_var(elem, name, value, flags) == FAILURE)
			return (FAILURE);
		p->argv = tab_remove_first_elem(&p->argc, p->argv);
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (SUCCESS);
}
