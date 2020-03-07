/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/03/07 15:44:41 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static int	parse_fc_option(char ***args)
{
	int	opt;
	int	opt_list;

	opt_list = 0;
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

void		free_subsitute(t_sub *substitute)
{
	t_sub	*tmp;

	while (substitute)
	{
		tmp = substitute->next;
		free(substitute->pat);
		free(substitute->rep);
		free(substitute);
		substitute = tmp;
	}
}

t_sub		*init_sub(char *pat, char *rep)
{
	t_sub	*new_sub;

	if (!(new_sub = (t_sub *)ft_memalloc(sizeof(t_sub))))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	new_sub->next = NULL;
	new_sub->pat = NULL;
	new_sub->rep = NULL;
	if (!pat || !rep)
		return (new_sub);
	if (!(new_sub->pat = ft_strdup(pat)) || !(new_sub->rep = ft_strdup(rep)))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	return (new_sub);
}

char		*fc_do_substitute(t_sub *sub_list)
{
	while (sub_list)
	{
		ft_printf("sub->rep: %s, sub->pat: %s\n", sub_list->rep, sub_list->pat);
		sub_list = sub_list->next;
	}
	return (NULL);
}

void		fc_replace_last_hist(char *tmp)
{
	ft_printf("Have to replace last cmd by %s\n", tmp);
}

int			exec_fc_s_opt(char **args)
{
	char	*tmp;
	int		status;
	t_sub	*sub_list;
	t_sub	*first;

	sub_list = NULL;
	first = sub_list;
	status = e_success;
	while (*args && (tmp = ft_strchr(*args, '=')))
	{
		*tmp++ = '\0';
		if (!(sub_list = init_sub(*args, tmp)))
			return (e_cannot_allocate_memory);
		sub_list = sub_list->next;
		*args += 1;
	}
	if (!get_matching_hist(&tmp, *args) && *args)
	{
		ft_printf("./21sh: fc: no command found\n");
		if (first->pat)
			free_subsitute(first);
		return (e_command_not_found);
	}
	tmp = g_hist->history_content + g_hist->offset + 1;
	if (!(tmp = fc_do_substitute(first)))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (e_cannot_allocate_memory);
	}
	ft_dprintf(STDERR_FILENO, "%s\n", tmp);
	fc_replace_last_hist(tmp);
	return (exec_input(tmp));
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
	ft_printf("opt: %d\n", opt_list);
	if (opt_list & FC_S_OPTION)
		status = exec_fc_s_opt(args);
	else
		ft_printf("please be patient it will come soon\n"); //status = exec_fc_other_opt(opt_list, args);
	return (0);
}
