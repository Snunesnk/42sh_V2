/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:04:33 by snunes            #+#    #+#             */
/*   Updated: 2020/04/17 13:35:49 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	add_alias(char **av)
{
	int			ret;
	char		*name;
	char		*value;

	ret = SUCCESS;
	while (*av && ret == SUCCESS)
	{
		ret = FAILURE;
		name = *av;
		if (get_assignment(*av, &name, &value) == SUCCESS && value[1])
		{
			*value = 0;
			ret = set_shell_var(name, value + 1, 0, &g_alias);
		}
		else if (!*name || *name == '=')
			ft_putstr_fd("alias: invalid alias name\n", 2);
		else
			ft_putstr_fd("alias: empty alias\n", 2);
		++av;
	}
	ft_merge_sort(&g_alias, alpha_sort);
	return (ret);
}

static void	print_alias_list(t_list *lst)
{
	t_shell_var	*svar;

	while (lst)
	{
		svar = (t_shell_var *)lst->content;
		ft_printf("alias %s='%s'\n", svar->name, svar->value);
		lst = lst->next;
	}
}

int			cmd_alias(int argc, char **argv)
{
	if (argc == 1)
		print_alias_list(g_alias);
	else
		return (add_alias(argv + 1));
	return (SUCCESS);
}
