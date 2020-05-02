/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:04:17 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/02 11:38:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

#define ESH e_command_not_found

int			set_temp_variable(char *assignment)
{
	char	*name;
	char	*value;

	if (get_assignment(assignment, &name, &value) == SUCCESS)
	{
		*value++ = 0;
		if (set_shell_var(name, value, SET | EXPORT | TEMP, &g_env) == SUCCESS)
			return (0);
	}
	return (1);
}

void		empty_env(t_list **svar_lst)
{
	t_list		*cur;
	t_shell_var	*svar;
	t_list		*new_env;

	new_env = NULL;
	while ((cur = ft_lst_pop(svar_lst, 0)))
	{
		svar = cur->content;
		if (svar->flag & TEMP)
			ft_lstaddend(&new_env, cur);
		else
			ft_lstaddend(&g_tmp_env, cur);
	}
	*svar_lst = new_env;
}

static int	env_path_concat(char **bin, char *beg, char *env, char *dir)
{
	char	*pathname;

	if (!(beg = get_shell_var("PATH", g_env))
		&& !(beg = get_shell_var("PATH", g_tmp_env)))
	{
		ft_memdel((void**)bin);
		return (e_command_not_found);
	}
	env = ft_strdup(beg);
	beg = env;
	while ((dir = ft_strsep(&env, ":")))
	{
		pathname = ft_strnjoin(3, dir, "/", *bin);
		if (!access(pathname, F_OK))
			break ;
		ft_memdel((void**)&pathname);
	}
	ft_memdel((void**)&beg);
	ft_memdel((void**)bin);
	if (dir)
	{
		*bin = pathname;
		return (e_success);
	}
	return (e_command_not_found);
}

static int	execute_env_process(char **argv, char **envp,
		t_hash_table *tmp, char *pathname)
{
	int				ret;

	if (!argv)
		return (0);
	if (is_a_builtin(argv[0]))
		return (builtins_dispatcher(argv));
	pathname = ft_strdup(argv[0]);
	if ((ret = check_type(pathname)) == e_success)
		return (process_execve(argv, envp, pathname));
	else if (ret != e_command_not_found)
	{
		ft_memdel((void**)&pathname);
		return (g_errordesc[psherror(ret, argv[0], e_cmd_type)].code);
	}
	if ((tmp = find_occurence(pathname)))
		return (process_execve(argv, envp, tmp->command_path));
	if (env_path_concat(&pathname, NULL, NULL, NULL) == e_command_not_found)
	{
		ft_memdel((void**)&pathname);
		return (g_errordesc[psherror(ESH, argv[0], e_cmd_type)].code);
	}
	else if (check_type(pathname) == e_success)
		return (process_execve(argv, envp, pathname));
	ft_memdel((void**)&pathname);
	return (psherror(e_command_not_found, argv[0], e_cmd_type));
}

int			exec_env_command(char **argv)
{
	char	**envp;
	int		ret;
	pid_t	pid;

	pid = 0;
	ret = 0;
	envp = get_env_tab();
	argv = ft_tabcpy(argv);
	if (!g_job_control_enabled || !(pid = fork()))
	{
		if (argv)
			ret = execute_env_process(argv, envp, NULL, NULL);
		exit_clean(ret);
	}
	else if (pid < 0)
	{
		ft_dprintf(STDERR_FILENO, "fork(2) failed\n");
		ret = 1;
	}
	else if (pid)
		waitpid(pid, &ret, WUNTRACED);
	ft_tabdel(&envp);
	ft_tabdel(&argv);
	return (ret);
}
