/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:03:13 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/21 16:20:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "builtins.h"

static int	check_access(char *arg)
{
	int ret;

	ret = e_success;
	if ((ret = access(arg, X_OK)))
	{
		psherror(e_permission_denied, arg, e_cmd_type);
		return (e_permission_denied);
	}
	return (e_success);
}

static int 	check_type(char *pathname)
{
	struct stat	buf;

	buf = (struct stat){.st_mode = 0};
	if (access(pathname, F_OK))
	{
		if (!ft_strncmp(pathname, "./", 2))
			return (e_no_such_file_or_directory);
		return (e_command_not_found);
	}
	if (stat(pathname, &buf))
		return (e_system_call_error);
	if (S_ISBLK(buf.st_mode))
		ft_printf("block device\n");
	else if (S_ISCHR(buf.st_mode))
		ft_printf("character device\n");
	else if (S_ISDIR(buf.st_mode))
		ft_printf("directory\n");
	else if (S_ISFIFO(buf.st_mode))
		ft_printf("FIFO/pipe\n");
	else if (S_ISLNK(buf.st_mode))
		ft_printf("symlink\n");
	else if (S_ISREG(buf.st_mode))
	{
		ft_printf("regular file\n");
		return (check_access(pathname));
	}
/*	else if (S_ISSOCK(buf.st_mode))
		ft_printf("socket\n");
*/	else
		ft_printf("unknown?\n");
	return (e_permission_denied);
}

static int	builtin_keyword_exec(char **argv)
{
	int	ret;

	ret = e_success;
	if (argv[1] && (ret = builtins_dispatcher(&argv[1])) != e_command_not_found)
	{
		return (ret);
	}
	else
	{
		psherror(e_no_builtin, argv[1], e_cmd_type);
		return (g_errordesc[e_no_builtin].code);
	}
}

static int	process_execve(char **argv, char **envp, char *pathname)
{
	int	ret;

	ret = execve(pathname, argv, envp);
	ft_tabdel(&argv);
	ft_tabdel(&envp);
	ft_memdel((void**)&pathname);
	exit(ret);
}

int	execute_process(char **argv, char **envp)
{
	int	ret;
	char	*pathname;

	if (!ft_strcmp(argv[0], "builtin"))
		return (builtin_keyword_exec(argv));
	else if (is_a_builtin(argv[0]))
		return (builtins_dispatcher(argv));
	pathname = ft_strdup(argv[0]);
	ret = check_type(pathname);
	if (ret == e_success)
		return (process_execve(argv, envp, pathname));
	else if (ret != e_command_not_found)
	{
		ft_memdel((void**)&pathname);
		psherror(ret, argv[0], e_cmd_type);
		return (g_errordesc[ret].code);
	}
	if (path_concat(&pathname) == e_command_not_found)
	{
	/*	ft_memdel((void**)&pathname);
	*/	psherror(e_command_not_found, argv[0], e_cmd_type);
		return (g_errordesc[ret].code);
	}
	else if (check_type(pathname) == e_success)
		return (process_execve(argv, envp, pathname));
	ft_memdel((void**)&pathname);
	psherror(e_command_not_found, argv[0], e_cmd_type);
	return (e_command_not_found);
}
