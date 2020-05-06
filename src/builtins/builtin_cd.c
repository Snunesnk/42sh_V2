#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

/*
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
{ // Case it goes home: cd
	cd->tmp = cd->path;
	if (!(cd->path = get_shell_var("HOME", g_env)))
	{
		pbierror("HOME not set");
		return (1);
	}
	if (cd->path)
		ft_memdel((void**)&cd->tmp);
	if (cd->path && !cd->path[0])
	{
		cd->path = NULL;
		cd->empty = 1;
		return (0);
	}
	if (cd->p)
		cd->path = ft_realpath(cd->path, NULL);
	else
		cd->path = ft_strdup(cd->path);
	return (0);
}

int	gfp_previous(struct s_cd *cd)
{ // Case it goes previous: cd -
	if (!(cd->oldpwd = get_shell_var("OLDPWD", g_env)))
	{
		pbierror("OLDPWD not set");
		g_optind = 1;
		return (e_invalid_input);
	}
	if (cd->oldpwd && !cd->oldpwd[0])
	{
		cd->oldpwd = NULL;
		cd->empty = 1;
		return (0);
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
	{
		cd->path = ft_resolvepath(cd->path);
		ft_printf("%s\n", cd->path);
	}
	else
	{
		cd->tmp = cd->path;
		cd->path = ft_strnjoin(3, g_pwd, "/", cd->tmp);
		ft_memdel((void**)&(cd->tmp));
	}
	cd->ret = e_success;
	return (0);
}

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
	if (set_shell_var("OLDPWD", cwd, EXPORT | SET, &g_env))
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
		if (set_shell_var("PWD", cwd, EXPORT | SET, &g_env))
			return (e_cannot_allocate_memory);
		if (g_pwd)
			ft_memdel((void**)&g_pwd);
		g_pwd = ft_strdup(cwd);
		ft_memdel((void**)&cwd);
	}
	else
	{
		if (set_shell_var("PWD", path, EXPORT | SET, &g_env))
			return (e_cannot_allocate_memory);
		if (g_pwd)
			ft_memdel((void**)&g_pwd);
		g_pwd = ft_strdup(path);
	}
	return (0);
}

int	cdpath_concat(char **path, char *env)
{
	char	*beg;
	char	*dir;
	char	*pathname;

	if (!(beg = get_shell_var("CDPATH", g_env)) || !beg[0])
		return (e_success);
	if (!(env = ft_strdup(beg)))
		return (e_cannot_allocate_memory);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		if (!(pathname = ft_strnjoin(3, dir, "/", *path)))
			return (e_cannot_allocate_memory);
		if (!access(pathname, X_OK))
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
		return (gfp_previous(cd));
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
		pbierror("%s: No such file or directory", cd->path);
	else
		pbierror("%s: No such file or directory",
			argv[g_optind]);
	ft_memdel((void**)&(cd->path));
	return (1);
}

static int	change_dir(const char *path, _Bool p, _Bool empty)
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
*/
int			cmd_cd(int argc, char **argv)
{
	int	err;

	err = 0;
	(void)argv;
	(void)argc;
/*	if ((err = cd_parse_opt(argc, argv, &cd.p)))
		return (err);
	if ((cd.ret = getfullpath(argv, &cd)))
		return (cd.ret);
	if (cd.empty)
		ft_printf("\n");
	if (!cd.empty && !(cd.tmp = ft_resolvepath(cd.path)))
	{
		pbierror("%s: %s", argv[g_optind], ft_strerror(g_errno));
		ft_memdel((void **)&(cd.path));
		return (1);
	}
	cd.path = cd.tmp;
	if (!cd.empty && stat(cd.path, &(cd.buf)))
		return (stat_failure(argv, &cd));
	if (!cd.empty && access(cd.path, X_OK))
		return (access_failure(argv, &cd));
	if ((cd.ret = change_dir(cd.path, cd.p, cd.empty)))
		return (changedir_failure(&cd));
	ft_memdel((void **)&(cd.path));
*/	return (err);
}
