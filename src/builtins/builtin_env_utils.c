/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:04:17 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/27 16:04:48 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

int		set_temp_variable(char *assignment)
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

void	empty_env(t_list **svar_lst)
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

int		exec_env_command(char **argv)
{
	char	**envp;
	int		ret;
	pid_t	pid;

	pid = 0;
	ret = 0;
	envp = get_env_tab();
	if (g_subshell || !(pid = fork()))
	{
		ret = execute_process(argv, envp, NULL, NULL);
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
	return (ret);
}
