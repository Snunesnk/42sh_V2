#include "shell.h"
#include "builtins.h"
#include "libft.h"
#include "error.h"

int cd_internal(char *directory, _Bool p_option);


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
/*
static int	concatenable_operand_while(const char *str)
{
	while (*str)
	{
		if (*str != '/')
			return (1);
		++str;
	}
	return (0);
}

static int	concatenable_operand(const char *str)
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
*/


static int	go_home(_Bool p_option)
{
	char	*home;

	home = get_shell_var("HOME", g_env);
//	1. If no directory operand is given and the HOME environment variable is empty or undefined, the default behavior is implementation-defined and no further steps shall be taken.
	if (!home)
	{
		pbierror("HOME not set");
		return (1);
	}
	else if (!home[0])
		return (0);
	else
//	2. If no directory operand is given and the HOME environment variable is set to a non-empty value, the cd utility shall behave as if the directory named in the HOME environment variable was specified as the directory operand.
		return (cd_internal(home, p_option));
}


/*
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
*/
static char	*concatenate_cdpath(char *directory)
{
	char	*cdpath;
	char	*cdpath_origin;
	char	*dir;
	char	*pathname;

//	5. Starting with the first pathname in the <colon>-separated pathnames of CDPATH
//	   (see the ENVIRONMENT VARIABLES section) if the pathname is non-null, test if the concatenation of that pathname,
//	   a <slash> character if that pathname did not end with a <slash> character, and the directory operand names
//	   a directory. If the pathname is null, test if the concatenation of dot, a <slash> character, and the operand
//	   names a directory. In either case, if the resulting string names an existing directory, set curpath to that
//	   string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH until all
//	   pathnames have been tested.
	cdpath = ft_strdup(get_shell_var("CDPATH", g_env));
	cdpath_origin = cdpath;
	if (!cdpath || !cdpath[0])
		return (NULL);
	while ((dir = ft_strsep(&cdpath, ":")))
	{
		pathname = ft_strnjoin(3, dir, "/", directory);
		pathname = ft_resolvepath(pathname);
		ft_printf("test: %s\n", pathname); // DEBUGG
		if (!access(pathname, X_OK))
			break ;
	}
	ft_printf("returned cdpath: %s\n", pathname); // DEBUGG
	if (pathname)
		ft_printf("%s\n", pathname);
	ft_memdel((void**)&cdpath_origin);
	return (pathname);
}
/*
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
*/
/*
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
*/
/*
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

int	cd_internal(char *directory, _Bool p_option)
{
	char	*curpath;
	char	*cdpath;

	curpath = NULL;
	cdpath = NULL;
//	1. & 2. if no dir, go_home (step 1. and 2.)
	if (!directory) // Case: cd | cd -L | cd -P
		return (go_home(p_option));
//	3. if the directory operand begins with a <slash> character, set curpath to the operand and proceed to step 7.
	else if (directory[0] == '/')
		curpath = directory;
//	4. If the first component of the directory operand is dot or dot-dot, proceed to step 6.
	else if (!ft_strcmp(directory, ".") || !ft_strcmp(directory, ".."))
		(void)directory;
//	5. Starting with the first pathname in the <colon>-separated pathnames of CDPATH
//	   (see the ENVIRONMENT VARIABLES section) if the pathname is non-null, test if the concatenation of that pathname,
//	   a <slash> character if that pathname did not end with a <slash> character, and the directory operand names
//	   a directory. If the pathname is null, test if the concatenation of dot, a <slash> character, and the operand
//	   names a directory. In either case, if the resulting string names an existing directory, set curpath to that
//	   string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH until all
//	   pathnames have been tested.
	else if ((cdpath = concatenate_cdpath(directory)))
		curpath = cdpath;
//	6. Set curpath to the directory operand.
	if (!curpath)
		curpath = directory;
//	7. If the -P option is in effect, proceed to step 10. If curpath does not begin with a <slash> character,
//	   set curpath to the string formed by the concatenation of the value of PWD, a <slash> character if the
//	   value of PWD did not end with a <slash> character, and curpath.
//	if (p_option)




//	8.

//	9.





//	10. The cd utility shall then perform actions equivalent to the chdir() function called with curpath as the
//	    path argument. If these actions fail for any reason, the cd utility shall display an appropriate error
//	    message and the remainder of this step shall not be executed. If the -P option is not in effect, the PWD
//	    environment variable shall be set to the value that curpath had on entry to step 9 (i.e., before conversion
//	    to a relative pathname). If the -P option is in effect, the PWD environment variable shall be set to the
//	    string that would be output by pwd -P. If there is insufficient permission on the new directory, or on any
//	    parent of that directory, to determine the current working directory, the value of the PWD environment
//	    variable is unspecified.




/*
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
*/
	return (1);
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
