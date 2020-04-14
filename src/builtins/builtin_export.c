/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/04/14 20:58:05 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

extern t_list	*g_env;

static void		print_export(void)
{
	t_list		*list;
	t_shell_var	*var;
	char		*name;
	char		*value;

	list = g_env;
	while (list)
	{
		var = ((t_shell_var*)(list->content));
		name = var->name;
		value = var->value;
		if ((var->flag & EXPORT))
		{
			if (value == NULL)
				ft_printf("declare -x %s\n", name);
			else
				ft_printf("declare -x %s=\"%s\"\n", name, value);
		}
		list = list->next;
	}
}

static void	add_env_var(char *name, char *value)
{
	t_list		*lst_new;
	t_shell_var	shell_var;

	shell_var.name = ft_strdup(name);
	shell_var.value = ft_strdup(value);
	shell_var.flag |= EXPORT;
	lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
	if (!lst_new)
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return ;
	}
	ft_lstadd(&g_env, lst_new);
	ft_merge_sort(&g_env, &alpha_sort);
}

static int	change_var_flag(int option, char *name, char *value)
{
	t_shell_var	*tmp;
	t_list		*list;

	list = g_env;
	while (list && !ft_strequ(((t_shell_var*)(list->content))->name, name))
		list = list->next;
	if (!list)
		return (0);
	tmp = (t_shell_var*)(list->content);
	tmp->flag = ((option & EXPORT_N_OPT)) ? SET : EXPORT + 1;
	if (value)
	{
		free(tmp->value);
		if (!(tmp->value = ft_strdup(value)))
		{
			ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
			return (0);
		}
	}
	return (1);
}

static void		exec_export(char **args, int option)
{
	char	*name;
	char	*value;

	if (!*args)
	{
		print_export();
		return ;
	}
	while ((name = *args))
	{
		value = ft_strchr(*args, '=');
		if (value)
		{
			*value = '\0';
			value += 1;
		}
		if (!change_var_flag(option, name, value))
			add_env_var(name, value);
		args += 1;
	}
}

int				cmd_export(int ac, char **av)
{
	int		ret;
	char	**args;
	int		option;

	option = 0;
	args = av + 1;
	while (ac > 1 && (ret = get_next_opt(&args, "pn")) != -1)
	{
		if (ret == 'p')
			option |= EXPORT_P_OPT;
		else if (ret == 'n')
			option |= EXPORT_N_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO, "./21sh: export: -%c: invalid option.\n" \
					, ret);
			ft_putendl_fd("export: usage: export [-n] [name[=value ...]]" \
				"or export -p", 2);
			return (e_invalid_input);
		}
	}
	exec_export(args, option);
	return (ret);
}
