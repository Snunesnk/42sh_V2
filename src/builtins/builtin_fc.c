/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/03/09 19:46:25 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	parse_fc_option(char ***args)
{
	int	opt;
	int	opt_list;

	opt_list = 0;
	opt_list |= FC_N_OPTION;
	while ((opt = get_next_opt(args, "e:lnrs")) != -1)
	{
		if (opt == 'n')
			opt_list |= FC_N_OPTION;
		else if (opt == 'l')
			opt_list |= FC_L_OPTION;
		else if (opt == 'r')
			opt_list |= FC_R_OPTION;
		else if (opt == 's')
			opt_list |= FC_S_OPTION;
		else if (opt == 'e')
			opt_list |= FC_E_OPTION;
		else
		{
			ft_dprintf(STDERR_FILENO, "%1$s: usage: %1$s [-e ename] [-lnr] " \
				"[first] [last] or fc -s [pat=rep] [command]\n", g_builtin_name);
			return (2);
		}
	}
	return (opt_list);
}



t_sub		*init_sub(t_sub *prev_sub)
{
	t_sub	*new_sub;

	if (!(new_sub = (t_sub *)ft_memalloc(sizeof(t_sub))))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	new_sub->next = NULL;
	new_sub->prev = prev_sub;
	new_sub->pat = NULL;
	new_sub->rep = NULL;
	return (new_sub);
}

t_sub		*fill_sub(t_sub *sub_list, char *pat, char *rep)
{
	if (!pat || !rep)
		return (sub_list);
	if (!(sub_list->pat = ft_strdup(pat)) || !(sub_list->rep = ft_strdup(rep)))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	return (sub_list);
}


char		*fc_do_substitute(char *str, t_sub *sub_list)
{
	char	*new_cmd;

	if (!(new_cmd = ft_strdup(str)))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	while (sub_list && sub_list->pat && sub_list->rep)
	{
		if (!(new_cmd = ft_strreplace(&new_cmd, sub_list->pat, sub_list->rep)))
		{
			ft_printf("./21sh: cannot allocate memory\n");
			return (NULL);
		}
		sub_list = sub_list->next;
	}
	return (new_cmd);
}

int			exec_fc_s_opt(char **args)
{
	char	*tmp;
	int		status;
	t_sub	*sub_list;

	if (!(sub_list = init_sub(NULL)))
		return (e_cannot_allocate_memory);
	status = e_success;
	while (*args && (tmp = ft_strchr(*args, '=')))
	{
		*tmp = '\0';
		tmp += 1;
		if (!(sub_list = fill_sub(sub_list, *args, tmp)))
			return (e_cannot_allocate_memory);
		if (!(sub_list->next = init_sub(sub_list)))
			return (e_cannot_allocate_memory);
		sub_list = sub_list->next;
		args += 1;
	}
	tmp = prev_hist();
	tmp = prev_hist();
	while (sub_list->prev)
		sub_list = sub_list->prev;
	if (*args && !(get_beg_matching_hist(&tmp, *args)))
	{
		ft_printf("./21sh: fc: no command found\n");
		if (sub_list->pat)
			free_substitute(sub_list);
		return (e_command_not_found);
	}
	if (!(tmp = fc_do_substitute(tmp, sub_list)))
		return (e_cannot_allocate_memory);
	free_substitute(sub_list);
	ft_dprintf(STDERR_FILENO, "%s\n", tmp);
	fc_replace_last_hist(tmp);
	return (exec_input(tmp));
	return (1);
}

int			cmd_fc(int argc, char **argv)
{
	char	**args;
	int		opt_list;
	int		status;

	(void)argc;
	if (!argv)
		return (e_invalid_input);
	args = argv + 1;
	g_builtin_name = argv[0];
	opt_list = parse_fc_option(&args);
	if (g_needed_arg && g_needed_arg[0] == '-' && g_needed_arg[1] == '\0')
		opt_list |= FC_S_OPTION;
	if (opt_list & FC_S_OPTION)
		status = exec_fc_s_opt(args);
	else
		status = exec_fc_other_opt(opt_list, args);
	return (status);
}
