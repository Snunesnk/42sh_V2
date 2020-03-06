/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:40 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/06 20:58:27 by snunes           ###   ########.fr       */
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
	if (S_ISDIR(buf.st_mode))
		return (e_is_a_directory);
	else if (S_ISREG(buf.st_mode))
		return (check_access(pathname));
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
	ft_perror("Failed to launch process using execve");
	ft_tabdel(&argv);
	ft_tabdel(&envp);
	ft_memdel((void**)&pathname);
	exit(ret);
}

int	execute_process(char **argv, char **envp)
{
	t_hash_table	*tmp;
	int				ret;
	char			*pathname;

	if (!*argv)
		return (0);
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
	if ((tmp = find_occurence(pathname)))
		return (process_execve(argv, envp, tmp->command_path));
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
