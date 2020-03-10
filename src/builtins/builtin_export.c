/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 16:26:27 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

extern t_list	*g_env;

static void		print_export(t_list *env, t_list **elem)
{
	char	*tmp;
	char	*name;
	char	*value;

	tmp = NULL;
	name = ((t_shell_var*)(env->content))->name;
	value = ((t_shell_var*)(env->content))->value;
	if ((((t_shell_var*)(env->content))->flag & EXPORT) == EXPORT)
	{
		if (((t_shell_var*)(env->content))->value == NULL)
			ft_asprintf(&tmp, "declare -x %s\n", name);
		else
		{
			ft_asprintf(&tmp, "declare -x %s=\"%s\"\n", name, value);
		}
	}
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
}

static int		get_flags(char **av, char *n_flag, char *p_flag)
{
	size_t		tab_i;
	size_t		str_i;

	tab_i = 0;
	while (av[tab_i] != NULL && av[tab_i][0] == '-')
	{
		str_i = 0;
		while (av[tab_i][str_i] != '\0')
		{
			if (av[tab_i][str_i] == 'n')
				*n_flag = 1;
			if (av[tab_i][str_i] == 'p')
				*p_flag = 1;
			str_i++;
		}
		tab_i++;
	}
	return (tab_i);
}

static void		remove_flag(char **av)
{
	size_t	i;
	t_list	*elem;
	char	*name;
	char	*tmp;

	i = 0;
	while (av[i] != NULL)
	{
		tmp = ft_strchr(av[i], '=');
		if (tmp != NULL)
			name = ft_strndup(av[i], tmp - av[i]);
		else
			name = ft_strdup(av[i]);
		elem = get_shell_var(name);
		((t_shell_var*)(elem->content))->flag &= ~(EXPORT);
		ft_strdel(&name);
		i++;
	}
}

int				cmd_export(int ac, char **av)
{
	int		ret;
	char	n_flag;
	char	p_flag;

	ret = SUCCESS;
	n_flag = 0;
	p_flag = 0;
	av++;
	if (ft_getopt(ac - 1, av, "np") == '?')
	{
		ft_putendl_fd("export: usage: export [-n] [name[=value ...]] \
or export -p", 2);
		ret = FAILURE;
	}
	else
	{
		av += get_flags(av, &n_flag, &p_flag);
		if (n_flag == 1)
			remove_flag(av);
		else if (ac != 1)
			ret = add_var(av);
		if (ac == 1 || p_flag == 1)
			ft_lstprint(g_env, &print_export);
	}
	return (ret);
}
