/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:04:33 by snunes            #+#    #+#             */
/*   Updated: 2020/05/20 21:47:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "quotes.h"

static int	print_alias(t_shell_var *svar)
{
	ft_printf("%s=", svar->name);
	single_quote_print_fd(svar->value, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

static int	print_single_alias(char *name, char *value)
{
	value = !value ? get_shell_var(name, g_alias) : value;
	if (!value)
		return (FAILURE);
	ft_printf("%s=", name);
	single_quote_print_fd(value, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}

static int	add_alias(char **av)
{
	int			ret;
	char		*name;
	char		*value;

	ret = SUCCESS;
	while (*++av)
	{
		name = *av;
		if (get_assignment(*av, &name, &value) == SUCCESS)
		{
			*value = 0;
			set_shell_var(name, value + 1, 0, &g_alias);
		}
		else if (!*name || *name == '=')
			ret = pbierror("'%s': invalid alias name", name);
		else if (print_single_alias(name, NULL) == FAILURE)
			ret = pbierror("'%s': not found", name);
	}
	ft_merge_sort(&g_alias, alpha_sort);
	return (!!ret);
}

int			cmd_alias(int argc, char **argv)
{
	if (argc == 1)
		print_shell_var(g_alias, print_alias);
	else
		return (add_alias(argv));
	return (0);
}
