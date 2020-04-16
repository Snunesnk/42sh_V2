/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_operand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 15:39:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "error.h"

extern char	g_pwd[];

int	concatenable_operand_while(const char *str)
{
	while (*str)
	{
		if (*str != '/')
			return (1);
		++str;
	}
	return (0);
}

int	concatenable_operand(const char *str)
{
	if (*str == '.')
	{
		++str;
		if (*str == '.')
		{
			++str;
			return (concatenable_operand_while(str));
		}
		else
			return (concatenable_operand_while(str));
	}
	return (concatenable_operand_while(str));
}

int	gfp_env(struct s_cd *cd)
{
	if (!(cd->path = get_shell_var_value("HOME", g_env)))
		if (!(cd->path = get_shell_var_value("PWD", g_env)))
			return (1);
	if (cd->p)
		cd->path = ft_realpath(cd->path, NULL);
	else
		cd->path = ft_strdup(cd->path);
	return (0);
}

int	gfp_previous(char **argv, struct s_cd *cd)
{
	if (!(cd->oldpwd = get_shell_var_value("OLDPWD", g_env)))
	{
		ft_dprintf(STDERR_FILENO,
				"%s: %s: OLDPWD not set\n", g_progname, argv[0]);
		g_optind = 1;
		return (e_invalid_input);
	}
	if (cd->p)
	{
		cd->oldpwd = ft_realpath(cd->oldpwd, NULL);
		cd->path = cd->oldpwd;
	}
	else
		cd->path = ft_strdup(cd->oldpwd);
	ft_printf("%s\n", cd->path);
	return (0);
}

int	gfp_concatenable(char **argv, struct s_cd *cd)
{
	cd->path = ft_strdup(argv[g_optind]);
	if ((cd->ret = cdpath_concat(&(cd->path),
					NULL)) == e_cannot_allocate_memory)
		return (g_errordesc[e_cannot_allocate_memory].code);
	else if (cd->ret == 3)
		ft_printf("%s\n", cd->path);
	else
	{
		cd->tmp = cd->path;
		cd->path = ft_strnjoin(3, g_pwd, "/", cd->tmp);
		ft_memdel((void**)&(cd->tmp));
	}
	cd->ret = e_success;
	return (0);
}
