/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:14:34 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/12 17:04:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

static int	error_cd(const char *msg, const char *curpath,
			const char *directory)
{
	if (ft_strcmp(directory, "-"))
		pbierror(msg, directory);
	else
		pbierror(msg, curpath);
	return (1);
}

static int	check_access(const char *curpath, const char *directory)
{
	struct stat	bf;

	if (access(curpath, F_OK))
		return (error_cd("%s: No such file or directory", curpath, directory));
	else if (stat(curpath, &bf))
		return (error_cd("stat(2) failed to find `%s'", curpath, directory));
	else if (!S_ISDIR(bf.st_mode))
		return (error_cd("%s: Not a directory", curpath, directory));
	else if (access(curpath, X_OK))
		return (error_cd("%s: Permission denied", curpath, directory));
	else if (!ft_strcmp(directory, "-"))
		ft_printf("%s\n", curpath);
	return (e_success);
}

static void	update_env(char *curpath)
{
	char	*oldpwd;

	oldpwd = get_shell_var("PWD", g_env);
	if (oldpwd)
		set_shell_var("OLDPWD", oldpwd, SET | EXPORT, &g_env);
	if (curpath && curpath[0])
		set_shell_var("PWD", curpath, SET | EXPORT, &g_env);
	else
	{
		oldpwd = getcwd(NULL, 0);
		set_shell_var("PWD", oldpwd, SET | EXPORT, &g_env);
		free(oldpwd);
	}
}

int			change_dir(char **curpath, const char *directory, _Bool p_option)
{
	if (!*curpath)
		return (0);
	if (!*curpath[0])
	{
		update_env(*curpath);
		return (0);
	}
	if (check_access(*curpath, directory))
		return (1);
	else if (chdir(*curpath))
	{
		pbierror("%s: chdir(2) failed to change directory", *curpath);
		return (2);
	}
	if (p_option)
		*curpath = absolute_path(curpath);
	if (*curpath)
		update_env(*curpath);
	return (e_success);
}
