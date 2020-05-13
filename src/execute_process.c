/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:40 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/12 21:40:23 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "builtins.h"

#define ESH e_command_not_found

static int	check_access(char *arg)
{
	int ret;

	ret = e_success;
	if ((ret = access(arg, X_OK)))
		return (e_permission_denied);
	return (e_success);
}

int			check_type(char *pathname)
{
	struct stat	buf;

	buf = (struct stat){.st_mode = 0};
	if (!ft_strchr(pathname, '/'))
		return (e_command_not_found);
	else if (access(pathname, F_OK))
		return (e_no_such_file_or_directory);
	if (stat(pathname, &buf))
		return (e_system_call_error);
	if (S_ISDIR(buf.st_mode))
		return (e_is_a_directory);
	else if (S_ISREG(buf.st_mode))
		return (check_access(pathname));
	return (e_permission_denied);
}

int			process_execve(char **argv, char **envp, char *pathname)
{
	execve(pathname, argv, envp);
	ft_tabdel(&argv);
	ft_tabdel(&envp);
	ft_memdel((void**)&pathname);
	exit_clean(0);
	return (0);
}

int			free_path_and_return(int ret, char **pathname, char *process_name)
{
	ft_memdel((void**)pathname);
	return (g_errordesc[psherror(ret, process_name, e_cmd_type)].code);
}

int			execute_process(char **argv, char **envp,
		t_hash_table *tmp, char *pathname)
{
	int	ret;

	if (!argv || !argv[0][0])
		return (0);
	if (is_a_builtin(argv[0]))
		return (builtins_dispatcher(argv));
	pathname = ft_strdup(argv[0]);
	if ((ret = check_type(pathname)) == e_success)
		return (process_execve(argv, envp, pathname));
	else if (ret != e_command_not_found)
		return (free_path_and_return(ret, &pathname, argv[0]));
	if ((tmp = find_occurence(pathname)))
		return (process_execve(argv, envp, tmp->command_path));
	if (path_concat(&pathname, NULL, NULL, NULL) == e_command_not_found)
		return (free_path_and_return(ESH, &pathname, argv[0]));
	else if (check_type(pathname) == e_success)
		return (process_execve(argv, envp, pathname));
	ft_memdel((void**)&pathname);
	return (g_errordesc[psherror(e_command_not_found, argv[0], \
				e_cmd_type)].code);
}
