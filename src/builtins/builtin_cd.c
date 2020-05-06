#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

int cd_internal(const char *directory, _Bool p_option);


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

static int	go_home(_Bool p_option)
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

static char	*concatenate_cdpath(const char *directory)
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

static int	check_access(const char *curpath, const char *directory)
{
	struct stat	bf;

	if (access(curpath, F_OK))
	{
		pbierror("%s: No such file or directory", directory);
		return (1);
	}
	else if (stat(curpath, &bf))
	{
		pbierror("stat(2) failed to find `%s'", directory);
		return (1);
	}
	else if (!S_ISDIR(bf.st_mode))
	{
		pbierror("%s: Not a directory", directory);
		return (1);
	}
	else if (access(curpath, X_OK))
	{
		pbierror("%s: Permission denied", directory);
		return (1);
	}
	return (e_success);
}

static int	change_dir(char *curpath, const char *directory, _Bool p_option)
{
	char	*oldpwd;

	if (!curpath || !curpath[0])
	{
	//	if (!curpath)
	//		curpath = ft_strdup("");
		return (0);
	}
	if (check_access(curpath, directory))
		return (1);
	else if (chdir(curpath))
	{
		pbierror("%s: chdir(2) failed to change directory", curpath);
		return (2);
	}
	if (p_option)
		curpath = ft_realpath(curpath, NULL);
	oldpwd = get_shell_var("PWD", g_env);
	set_shell_var("OLDPWD", oldpwd, SET | EXPORT, &g_env);
	set_shell_var("PWD", curpath, SET | EXPORT, &g_env);
	return (e_success);
}

static char	*concatenate_pwd(const char *directory)
{
	char	*curpath;
	char	*pwd;
	int	i;

	pwd  = get_shell_var("PWD", g_env);
	if (!pwd || !pwd[0])
		return (NULL);
	i = ft_strlen(pwd);
	if (pwd[i] != '/')
		curpath = ft_strnjoin(3, pwd, "/", directory);
	else
		curpath = ft_strjoin(pwd, directory);
	return (curpath);
}

static char	*concatenate_oldpwd(void)
{
	char	*curpath;

	curpath = get_shell_var("OLDPWD", g_env);
	if (!curpath)
	{
		pbierror("OLDPWD not set\n");
		curpath = ft_strdup("");
	}
	else if (curpath[0])
		curpath = ft_strdup(curpath);
	ft_printf("%s\n", curpath);
	return (curpath);
}

int	cd_internal(const char *directory, _Bool p_option)
{
	char	*curpath;
	char	*cdpath;
	int	err;

	curpath = NULL;
	cdpath = NULL;
	if (!directory)
		return (go_home(p_option));
	else if (directory[0] == '/')
		curpath = ft_strdup(directory);
	else if (!ft_strcmp(directory, ".") || !ft_strcmp(directory, ".."))
		(void)curpath;
	else if (!ft_strcmp(directory, "-"))
		curpath = concatenate_oldpwd();
	else if ((cdpath = concatenate_cdpath(directory)))
		curpath = cdpath;
	if (!curpath)
		curpath = concatenate_pwd(directory);
	curpath = ft_resolvepath(curpath);
	if (ft_strlen(curpath) + 1 > PATH_MAX)
		return (2);
	err = change_dir(curpath, directory, p_option);
	ft_memdel((void**)&curpath);
	return (err);
}

int			cmd_cd(int argc, char **argv)
{
	_Bool	p_option;

	p_option = 0;
	if (cd_parse_opt(argc, argv, &p_option))
		return (2);
	else
		return (cd_internal(argv[g_optind], p_option));
}
