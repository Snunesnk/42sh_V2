/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/03 18:49:45 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

extern t_list	*g_env;

static void	print_export(t_list *env, t_list **elem)
{
	char	*tmp;

	tmp = NULL;
	if ((((t_shell_var*)(env->content))->flag & EXPORT) == EXPORT)
	{
		if (((t_shell_var*)(env->content))->value == NULL)
			ft_asprintf(&tmp, "declare -x %s\n", ((t_shell_var*)(env->content))->name);
		else
		{
			ft_asprintf(&tmp, "declare -x %s=\"%s\"\n", ((t_shell_var*)(env->content))->name,
					((t_shell_var*)(env->content))->value);
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

static t_list	*get_shell_var(char *name)
{
	t_list	*head;
	t_list	*elem;

	head = g_env;
	elem = NULL;
	while (g_env != NULL)
	{
		if (ft_strequ(name, ((t_shell_var*)(g_env->content))->name))
		{
			elem = g_env;
			break ;
		}
		g_env = g_env->next;
	}
	g_env = head;
	return (elem);
}

static int		add_var(char **av)
{
	t_shell_var	shell_var;
	t_list		*lst_new;
	t_list		*elem;
	char		*name;
	char		*value;
	size_t		i;

	i= 0;
	ft_bzero(&shell_var, sizeof(shell_var));
	while (av[i] != NULL)
	{
		value = ft_strchr(av[i], '=');
		if (value != NULL)
		{
			name = ft_strndup(av[i], value - av[i]);
			value = ft_strdup(value + 1);
		}
		else
			name = ft_strdup(av[i]);
		elem = get_shell_var(name);
		if (elem != NULL)
		{
			if (value != NULL)
				((t_shell_var*)(elem->content))->value = value;
			((t_shell_var*)(elem->content))->flag |= SET;
			((t_shell_var*)(elem->content))->flag |= EXPORT;
		}
		else
		{
			shell_var.name = name;
			if (value != NULL)
			{
				shell_var.value = value;
				shell_var.flag |= SET;
			}
			shell_var.flag |= EXPORT;
			lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
			if (lst_new == NULL)
				return (FAILURE);
			ft_lstadd(&g_env, lst_new);
		}
		i++;
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (SUCCESS);
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
	if (ft_getopt(ac - 1, av, "np") == FALSE)
	{
		ft_putendl_fd("export: usage: export [-n] [name[=value ...]] or export -p", 2);
		ret = FAILURE;
	}
	else
	{
		av += get_flags(av, &n_flag, &p_flag);
		if (n_flag == 1)
			remove_flag(av);
		else
			ret = add_var(av);
		if (ac == 1 || p_flag == 1)
			ft_lstprint(g_env, &print_export);
	}
	return (ret);
}
