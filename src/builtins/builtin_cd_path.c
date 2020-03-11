/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 18:01:02 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "error.h"

extern char	g_pwd[];

int	set_oldpwd(void)
{
	char	*cwd;
	_Bool	allocated;

	allocated = 0;
	if (!(cwd = g_pwd))
	{
		allocated = 1;
		if (!(cwd = getcwd(NULL, 0)))
			return (e_system_call_error);
	}
	if (ft_setenv("OLDPWD", cwd, 1))
	{
		if (allocated)
			ft_memdel((void**)&cwd);
		return (e_cannot_allocate_memory);
	}
	if (allocated)
		ft_memdel((void**)&cwd);
	return (0);
}

int	refresh_pwd(const char *path, _Bool p)
{
	char	*cwd;

	if (p)
	{
		if (!(cwd = getcwd(NULL, 0)))
			return (e_system_call_error);
		if (ft_setenv("PWD", cwd, 1))
			return (e_cannot_allocate_memory);
		ft_bzero((void*)g_pwd, sizeof(g_pwd));
		ft_strncpy(g_pwd, cwd, sizeof(g_pwd));
		ft_memdel((void**)&cwd);
	}
	else
	{
		if (ft_setenv("PWD", path, 1))
			return (e_cannot_allocate_memory);
		ft_bzero((void*)g_pwd, sizeof(g_pwd));
		ft_strncpy(g_pwd, path, sizeof(g_pwd));
	}
	return (0);
}

int	cdpath_concat(char **path, char *env)
{
	char	*beg;
	char	*dir;
	char	*pathname;

	if (!(beg = ft_getenv("CDPATH")))
		return (e_success);
	if (!(env = ft_strdup(beg)))
		return (e_cannot_allocate_memory);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		if (!(pathname = ft_strnjoin(3, dir, "/", *path)))
			return (e_cannot_allocate_memory);
		if (!access(pathname, F_OK))
			break ;
		ft_memdel((void**)&pathname);
	}
	ft_memdel((void**)&beg);
	if (dir)
	{
		ft_memdel((void**)path);
		*path = pathname;
		return (3);
	}
	return (e_success);
}

int	getfullpath(char **argv, struct s_cd *cd)
{
	if (!argv[g_optind])
		return (gfp_env(cd));
	else if (!ft_strcmp(argv[g_optind], "-"))
		return (gfp_previous(argv, cd));
	else if (*(argv[g_optind]) == '/')
		cd->path = ft_strdup(argv[g_optind]);
	else if (concatenable_operand(argv[g_optind]))
		return (gfp_concatenable(argv, cd));
	else
	{
		cd->path = ft_strdup(argv[g_optind]);
		cd->tmp = cd->path;
		cd->path = ft_strnjoin(3, g_pwd, "/", cd->tmp);
		ft_memdel((void**)&(cd->tmp));
	}
	return (0);
}

int	stat_failure(char **argv, struct s_cd *cd)
{
	if (!argv[g_optind] || !*argv[g_optind])
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: %s: No such file or directory\n",
		g_progname, argv[0], cd->path);
	}
	else
	{
		ft_dprintf(STDERR_FILENO,
		"%s: %s: %s: No such file or directory\n",
		g_progname, argv[0], argv[g_optind]);
	}
	ft_memdel((void**)&(cd->path));
	return (1);
}
