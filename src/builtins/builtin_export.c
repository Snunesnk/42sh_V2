/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/04/18 21:19:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	print_export(void)
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
	return (0);
}

static int	exec_export(char **args, int option)
{
	char		*name;
	char		*value;
	uint64_t	flags;
	int			ret;

	ret = SUCCESS;
	flags = !(option & EXPORT_N_OPT) ? EXPORT : 0;
	while ((name = *args++))
	{
		if (get_assignment(name, &name, &value) == SUCCESS)
			*value++ = 0;
		if (!*name || *name == '=')
			ret = pbierror(g_builtin_name,
				"'%s': not a valid identifier", name);
		else if (value)
			set_shell_var(name, value, flags | SET, &g_env);
		else if (flags)
		{
			if (flag_shell_var(name, flags >> SHVAR_ADD_OFF, g_env) == FAILURE)
				set_shell_var(name, value, flags, &g_env);
		}
		else
			flag_shell_var(name, EXPORT >> SHVAR_RM_OFF, g_env);
	}
	return (!!ret);
}

int			cmd_export(int ac, char **av)
{
	int		ret;
	char	**args;
	int		option;

	option = 0;
	args = av + 1;
	g_builtin_name = av[0];
	while (ac > 1 && (ret = get_next_opt(&args, "pn")) != -1)
	{
		if (ret == 'p')
			option |= EXPORT_P_OPT;
		else if (ret == 'n')
			option |= EXPORT_N_OPT;
		else
		{
			pbierror("-%c: invalid option.", ret);
			ft_dprintf(STDERR_FILENO,
					"%1$s: usage: %1$s [-n] [name[=value ...]] or %1$s -p\n",
					g_builtin_name);
			return (1);
		}
	}
	if (!*args)
		return (print_export());
	return (exec_export(args, option));
}
