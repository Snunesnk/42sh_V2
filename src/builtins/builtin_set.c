/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:43:11 by efischer          #+#    #+#             */
/*   Updated: 2020/04/12 23:34:24 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

_Bool	g_hashall = 1;
_Bool	g_history = 1;
_Bool	g_histexpand = 1;
_Bool	g_onecmd = 0;
_Bool	g_verbose = 0;
_Bool	g_emacs = 1;
_Bool	g_vim = 0;
int		g_jump_arg = 0;

static void	print_set(t_list *env, t_list **elem)
{
	char	*tmp;

	tmp = NULL;
	if ((((t_shell_var*)(env->content))->flag & SET) == SET)
	{
		ft_asprintf(&tmp, "%s=\"%s\"\n", ((t_shell_var*)(env->content))->name,
				((t_shell_var*)(env->content))->value);
	}
	*elem = ft_lstnew(tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

static void	print_variables(char **args, t_o_options *option_list)
{
	int	i;
	int	active;
	int	sign;

	i = 0;
	sign = (**args == '-') ? 1 : 0;
	while (i < 7)
	{
		active = *(option_list[i].variable);
		if (sign)
		{
			ft_printf("%-15s\t%s\n", option_list[i].name, \
					(active) ? "on" : "off");
		}
		else
		{
			ft_printf("set %co %s\n", (active) ? '+' : '-', \
					option_list[i].name);
		}
		i++;
	}
}

static void	exec_o_opt(char ***args, t_o_options *option_list)
{
	char	*name;
	int		i;

	i = 0;
	name = *(*args + 1);
	if (!name || name[0] == '-' || name[0] == '+')
	{
		print_variables(*args, option_list);
		return ;
	}
	while (i < 7 && !ft_strequ(name, option_list[i].name))
		i++;
	if (i == 7)
		return ;
	*(option_list[i].variable) = (***args == '-') ? 1 : 0;
	if (ft_strequ(name, "emacs") || ft_strequ(name, "vi"))
		change_binding(&option_list, name);
	g_jump_arg = 1;
}

static int	flip_opt(char opt, char ***args)
{
	static t_o_options		option_list[] = { \
		{"emacs", '\0', &g_emacs}, \
		{"hashall", 'h', &g_hashall}, \
		{"histexpand", 'H', &g_histexpand}, \
		{"history", '\0', &g_history}, \
		{"onecmd", 't', &g_onecmd}, \
		{"verbose", 'v', &g_verbose}, \
		{"vi", '\0', &g_vim}};
	int						i;

	i = 0;
	if (opt == 'o')
	{
		exec_o_opt(args, option_list);
		return (e_success);
	}
	while (i < 7 && option_list[i].value != opt)
		i++;
	if (i == 7)
		return (-1);
	if (***args == '-')
		*(option_list[i].variable) = 1;
	else
		*(option_list[i].variable) = 0;
	return (e_success);
}

int			cmd_set(int ac, char **av)
{
	extern t_list			*g_env;
	char					**args;
	int						i;

	if (ac == 1)
		ft_lstprint(g_env, &print_set);
	args = av + 1;
	g_builtin_name = av[0];
	while (ac > 1 && args && *args && ((*args)[0] == '-' || (*args)[0] == '+'))
	{
		g_jump_arg = 0;
		i = 1;
		while ((*args)[i])
		{
			if (flip_opt((*args)[i], &args) == -1)
			{
				ft_printf("./21sh: set: -%c: invalid option\nset: usage: set" \
						"[-hHtv] [-o option_name] [arg ...]\n", (*args)[i]);
				return (e_invalid_input);
			}
			i++;
		}
		args += g_jump_arg + 1;
	}
	return (e_success);
}
