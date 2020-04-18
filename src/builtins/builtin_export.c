/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/04/18 02:06:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static void	print_export(void)
{
	t_list		*list;
	t_shell_var	*var;
	char		*name;
	char		*value;

	list = g_env;
	while (list)
	{
		var = ((t_shell_var*)(list->content));
		name = var->name;
		value = var->value;
		if ((var->flag & EXPORT))
		{
			if (value == NULL)
				ft_printf("declare -x %s\n", name);
			else
				ft_printf("declare -x %s=\"%s\"\n", name, value);
		}
		list = list->next;
	}
}

static void	exec_export(char **args, int option)
{
	char		*name;
	char		*value;
	uint64_t	flags;

	if (!*args)
		print_export();
	flags = !(option & EXPORT_N_OPT) ? EXPORT : 0;
	while ((name = *args))
	{
		if (get_assignment(*args, &name, &value) == SUCCESS)
			*value++ = 0;
		if (!*name || *name == '=')
			ft_dprintf(STDERR_FILENO,
				"export: `%s': not a valid identifier\n", name);
		else if (value)
			set_shell_var(name, value, flags | SET, &g_env);
		else if (flags)
		{
			if (flag_shell_var(name, flags >> SHVAR_ADD_OFF, g_env) == FAILURE)
				set_shell_var(name, value, flags, &g_env);
		}
		else
			flag_shell_var(name, EXPORT >> SHVAR_RM_OFF, g_env);
		++args;
	}
}

int			cmd_export(int ac, char **av)
{
	int		ret;
	char	**args;
	int		option;

	option = 0;
	args = av + 1;
	while (ac > 1 && (ret = get_next_opt(&args, "pn")) != -1)
	{
		if (ret == 'p')
			option |= EXPORT_P_OPT;
		else if (ret == 'n')
			option |= EXPORT_N_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO, "./21sh: export: -%c: invalid option.\n" \
					, ret);
			ft_putendl_fd("export: usage: export [-n] [name[=value ...]]" \
				"or export -p", 2);
			return (e_invalid_input);
		}
	}
	exec_export(args, option);
	return (e_success);
}
