/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 16:47:14 by yforeau          ###   ########.fr       */
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
			ft_dprintf(STDERR_FILENO,
					"%1$s: usage: %1$s [-L|-P] [dir]\n", argv[0]);
			return (2);
		}
	}
	return (e_success);
}

static int	access_failure(char **argv, struct s_cd *cd)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: Permission denied\n",
			g_progname, argv[0], argv[g_optind]);
	ft_memdel((void**)&cd->path);
	return (1);
}

static int	changedir_failure(char **argv, struct s_cd *cd)
{
	if (cd->ret != e_invalid_input)
	{
		psherror(cd->ret, argv[0], e_cmd_type);
		ft_memdel((void**)&(cd->path));
		return (g_errordesc[cd->ret].code);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
		g_progname, argv[0], cd->path,
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
	cd.path = ft_resolvepath(cd.path);
	if (!cd.path)
		return (1);
	if (stat(cd.path, &(cd.buf)))
		return (stat_failure(argv, &cd));
	if (access(cd.path, F_OK))
		return (access_failure(argv, &cd));
	if ((cd.ret = change_dir(cd.path, cd.p)))
		return (changedir_failure(argv, &cd));
	return (cd.ret);
}
