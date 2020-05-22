/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:04:17 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/22 19:47:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

int			set_temp_variable(char *assignment)
{
	char	*name;
	char	*value;
	int		already_exist;

	if (get_assignment(assignment, &name, &value) == SUCCESS)
	{
		*value++ = 0;
		already_exist = !!get_shell_var(name, g_env);
		if (set_shell_var(name, value, SET | EXPORT | TEMP, &g_env) == SUCCESS)
		{
			if (!already_exist)
				ft_lstaddend(&g_env, ft_lst_pop(&g_env, 0));
			return (0);
		}
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
			unset_shell_var(svar->name, &cur);
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

static int	free_and_return(int ret, char **pathname, char *command_name)
{
	ft_memdel((void**)pathname);
	pbierror("'%s': %s", command_name, g_errordesc[ret].message);
	return (g_errordesc[ret].code);
}

int			execute_env_process(char **argv, char **envp,
		t_hash_table *tmp, char *pathname)
{
	int	ret;

	if (!argv || !argv[0][0])
		return (0);
	pathname = ft_strdup(argv[0]);
	if ((ret = check_type(pathname, 1)) == e_success)
		return (process_execve(argv, envp, pathname));
	else if (ret != e_command_not_found)
		return (free_and_return(ret, &pathname, argv[0]));
	tmp = find_occurence(pathname);
	if (tmp && !access(tmp->command_path, F_OK))
		return (process_execve(argv, envp, tmp->command_path));
	if (env_path_concat(&pathname, NULL, NULL, NULL) == e_command_not_found)
		return (free_and_return(e_command_not_found, &pathname, argv[0]));
	else if (check_type(pathname, 1) == e_success)
		return (process_execve(argv, envp, pathname));
	return (free_and_return(e_command_not_found, &pathname, argv[0]));
}
