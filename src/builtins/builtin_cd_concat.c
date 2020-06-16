/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_concat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:14:34 by abarthel          #+#    #+#             */
/*   Updated: 2020/06/16 16:52:09 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

int		go_home(_Bool p_option)
{
	char	*home;

	home = get_shell_var("HOME", g_env);
	if (!home)
	{
		pbierror("HOME not set");
		return (1);
	}
	else if (!home[0])
		return (0);
	else
		return (cd_internal(home, p_option));
}

char	*concatenate_cdpath(const char *directory)
{
	char	*cdpath;
	char	*cdpath_origin;
	char	*dir;
	char	*pathname;

	pathname = NULL;
	cdpath = get_shell_var("CDPATH", g_env);
	if (!cdpath || !cdpath[0])
		return (NULL);
	cdpath = ft_strdup(cdpath);
	cdpath_origin = cdpath;
	while ((dir = ft_strsep(&cdpath, ":")))
	{
		pathname = ft_strnjoin(3, dir, "/", directory);
		pathname = ft_resolvepath(pathname);
		if (!access(pathname, X_OK))
			break ;
		ft_memdel((void**)&pathname);
	}
	if (pathname)
		ft_printf("%s\n", pathname);
	ft_memdel((void**)&cdpath_origin);
	return (pathname);
}

char	*absolute_path(char **curpath)
{
	char *tmp;

	if (*curpath)
	{
		tmp = ft_realpath(*curpath, NULL);
		ft_memdel((void**)curpath);
		return (tmp);
	}
	return (NULL);
}

char	*concatenate_pwd(const char *directory)
{
	char	*curpath;
	char	*pwd;
	int		i;
	_Bool	allocated;

	allocated = 0;
	pwd = get_shell_var("PWD", g_env);
	if (!pwd || !pwd[0] || access(pwd, F_OK))
	{
		pwd = getcwd(NULL, 0);
		allocated = 1;
	}
	if (!pwd)
		return (NULL);
	i = ft_strlen(pwd);
	if (pwd[i] != '/')
		curpath = ft_strnjoin(3, pwd, "/", directory);
	else
		curpath = ft_strjoin(pwd, directory);
	if (allocated)
		ft_memdel((void**)&pwd);
	return (curpath);
}

char	*get_oldpwd(void)
{
	char	*curpath;

	curpath = get_shell_var("OLDPWD", g_env);
	if (!curpath)
		pbierror("OLDPWD not set");
	else
		curpath = ft_strdup(curpath);
	if (curpath && !curpath[0])
		ft_printf("%s\n", curpath);
	return (curpath);
}
