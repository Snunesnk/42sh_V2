/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/16 10:41:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	print_export(t_shell_var *svar)
{
	char	*value;

	if ((svar->flag & EXPORT) && !(svar->flag & TEMP))
	{
		value = svar->flag & TEMP ? get_shell_var(svar->name, g_tmp_env)
			: svar->value;
		if (value == NULL)
			ft_printf("export %s\n", svar->name);
		else
			ft_printf("export %s=\"%s\"\n", svar->name, value);
	}
	return (0);
}

static void	export_var(char *name, char *value, uint64_t flags)
{
	if (unset_shell_var(name, &g_tmp_env) == SUCCESS)
	{
		if (value)
			set_shell_var(name, value, TEMP >> SHVAR_RM_OFF, &g_env);
	}
	else if (value)
		set_shell_var(name, value, flags | SET, &g_env);
	else if (flags)
	{
		if (flag_shell_var(name, flags >> SHVAR_ADD_OFF, g_env) == FAILURE)
			set_shell_var(name, value, flags, &g_env);
	}
	else
		flag_shell_var(name, EXPORT >> SHVAR_RM_OFF, g_env);
	flag_shell_var(name, TEMP >> SHVAR_RM_OFF, g_env);
}

static int	exec_export(char **args, int option)
{
	char		*value;
	char		*name;
	uint64_t	flags;
	int			ret;

	ret = SUCCESS;
	flags = !(option & EXPORT_N_OPT) ? EXPORT : 0;
	while ((name = *args++))
	{
		if (get_assignment(name, &name, &value) == SUCCESS)
			*value++ = 0;
		if (!*name || *name == '=')
			ret = pbierror("'%s': not a valid identifier", name);
		else
			export_var(name, value, flags);
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
			return (2);
		}
	}
	if (!*av)
		print_shell_var(g_env, print_export);
	ret = exec_export(av, option);
	set_temp_shell_variables();
	return (ret);
}
