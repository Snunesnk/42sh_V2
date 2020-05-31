/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:14:34 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/28 15:29:34 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

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
	if (argc - g_optind > 1)
	{
		pbierror("%s: too many arguments", g_builtin_name);
		return (1);
	}
	return (e_success);
}

int			cd_internal(char *directory, _Bool p_option)
{
	char	*curpath;
	char	*cdpath;
	int		err;

	curpath = NULL;
	cdpath = NULL;
	if (!directory)
		return (go_home(p_option));
	else if (directory[0] == '/')
		curpath = ft_strdup(directory);
	else if (!ft_strncmp(directory, ".", 1) || !ft_strncmp(directory, "..", 2))
		curpath = concatenate_pwd(directory);
	else if (!ft_strcmp(directory, "-"))
		curpath = get_oldpwd();
	else if ((cdpath = concatenate_cdpath(directory)))
		curpath = cdpath;
	else
		curpath = concatenate_pwd(directory);
	if (!curpath)
		return (1);
	if (curpath[0] == '/' && !access(curpath, F_OK))
		curpath = ft_resolvepath(curpath);
	err = change_dir(&curpath, directory, p_option);
	ft_memdel((void**)&curpath);
	return (err);
}

int			cmd_cd(int argc, char **argv)
{
	_Bool	p_option;
	int		err;

	p_option = 0;
	if ((err = cd_parse_opt(argc, argv, &p_option)))
		return (err);
	else
		return (cd_internal(argv[g_optind], p_option));
}
