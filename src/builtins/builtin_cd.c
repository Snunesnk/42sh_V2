/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 08:20:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

extern char	g_pwd[];

static int	change_dir(const char *path, _Bool p)
{
	int	ret;

	if (chdir(path))
		return (e_invalid_input);
	if ((ret = set_oldpwd()))
		return (ret);
	if ((ret = refresh_pwd(path, p)))
		return (ret);
	return (e_success);
}

static int	cd_parse_opt(int argc, char **argv, _Bool *p)
{
	int	opt;

	*p = 0;
	g_opterr = 1;
	g_optind = 1;
	while ((opt = ft_getopt(argc, argv, "+LP")) != -1)
	{
		if (opt == 'P')
			*p |= 1;
		else if (opt == '?')
		{
			pbierror("usage: %s [-L|-P] [dir]", g_builtin_name);
			return (2);
		}
	}
	return (e_success);
}

static int	access_failure(char **argv, struct s_cd *cd)
{
	pbierror("%s: Permission denied", argv[g_optind]);
	ft_memdel((void**)&cd->path);
	return (1);
}

static int	changedir_failure(struct s_cd *cd)
{
	if (cd->ret != e_invalid_input)
	{
		psherror(cd->ret, g_builtin_name, e_cmd_type);
		ft_memdel((void**)&(cd->path));
		return (g_errordesc[cd->ret].code);
	}
	else
	{
		pbierror("%s: %s", cd->path,
		g_errordesc[e_no_such_file_or_directory].message);
		ft_memdel((void**)&(cd->path));
		return (e_invalid_input);
	}
}

int			cmd_cd(int argc, char **argv)
{
	struct s_cd	cd;

	cd.path = NULL;
	if ((cd.ret = cd_parse_opt(argc, argv, &cd.p)))
		return (cd.ret);
	if ((cd.ret = getfullpath(argv, &cd)))
		return (cd.ret);
	if (!(cd.tmp = ft_resolvepath(cd.path)))
	{
		ft_memdel((void **)&(cd.path));
		return (1);
	}
	cd.path = cd.tmp;
	if (stat(cd.path, &(cd.buf)))
		return (stat_failure(argv, &cd));
	if (access(cd.path, F_OK))
		return (access_failure(argv, &cd));
	if ((cd.ret = change_dir(cd.path, cd.p)))
		return (changedir_failure(&cd));
	ft_memdel((void **)&(cd.path));
	return (cd.ret);
}
