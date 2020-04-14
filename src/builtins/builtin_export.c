/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/04/14 16:04:20 by snunes           ###   ########.fr       */
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
static t_list	*get_env_var(char *name)
{
	t_list	*list;
	char	*var_name;

	list = g_env;
	while (list)
	{
		var_name = ((t_shell_var*)(list->content))->name;
		if (ft_strequ(name, var_name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

static t_list	*change_var_flag(int option, char *value, t_list *var)
{
	t_shell_var	*tmp;

	tmp = (t_shell_var*)(var->content);
	if ((option & EXPORT_N_OPT))
		tmp->flag = SET;
	else
		tmp->flag |= EXPORT;
	if (value)
	{
		free(tmp->value);
		if (!(tmp->value = ft_strdup(value)))
		{
			ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
			return (NULL);
		}
	}
	return (var);
}

static void		exec_export(char **args, int option)
{
	t_list	*var;
	char	*name;
	char	*tmp;

	var = NULL;
	if (!*args)
	{
		print_export();
		return ;
	}
	while ((name = *args))
	{
		tmp = ft_strchr(*args, '=');
		if (tmp)
		{
			*tmp = '\0';
			tmp += 1;
		}
		var = get_env_var(name);
		if (var)
			var = change_var_flag(option, tmp, var);
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
