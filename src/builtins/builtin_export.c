/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/27 12:20:11 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	print_export(t_shell_var *svar)
{
	if (svar->flag & EXPORT)
	{
		if (svar->value == NULL)
			ft_printf("declare -x %s\n", svar->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", svar->name, svar->value);
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
	int		option;

	++av;
	option = 0;
	while (ac > 1 && (ret = get_next_opt(&av, "pn")) != -1)
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
	if (*av)
		return (exec_export(av, option));
	print_shell_var(g_env, print_export);
	return (0);
}
