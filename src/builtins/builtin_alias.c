/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:04:33 by snunes            #+#    #+#             */
/*   Updated: 2020/04/18 17:45:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	print_alias(char *name, char *value)
{
	value = !value ? get_shell_var(name, g_alias) : value;
	if (!value)
		return (FAILURE);
	ft_printf("alias %s='%s'\n", name, value);
	return (SUCCESS);
}

static void	print_alias_list(t_list *lst)
{
	t_shell_var	*svar;

	while (lst)
	{
		svar = (t_shell_var *)lst->content;
		print_alias(svar->name, svar->value);
		lst = lst->next;
	}
}

static int	add_alias(char **av, char *builtin_name)
{
	int			ret;
	char		*name;
	char		*value;

	ret = SUCCESS;
	while (*++av && ret == SUCCESS)
	{
		ret = FAILURE;
		name = *av;
		if (get_assignment(*av, &name, &value) == SUCCESS && value[1])
		{
			*value = 0;
			ret = set_shell_var(name, value + 1, 0, &g_alias);
		}
		else if (!*name || *name == '=')
			pbierror(builtin_name, "'%s': invalid alias name", name);
		else if ((ret = print_alias(name, NULL)) == FAILURE)
			pbierror(builtin_name, "'%s': not found", name);
	}
	ft_merge_sort(&g_alias, alpha_sort);
	return (!!ret);
}

int			cmd_alias(int argc, char **argv)
{
	if (argc == 1)
		print_alias_list(g_alias);
	else
		return (add_alias(argv, argv[0]));
	return (0);
}
