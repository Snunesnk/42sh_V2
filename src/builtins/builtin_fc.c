/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/03/08 17:47:04 by snunes           ###   ########.fr       */
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

char		*ft_strreplace(char **str, char *pattern, char *replacement)
{
	char	*tmp;
	int		nb_occur;
	int		pat_len;
	int		rep_len;
	int		str_len;

	tmp = *str;
	nb_occur = 0;
	pat_len = (int)ft_strlen(pattern);
	rep_len = (int)ft_strlen(replacement);
	str_len = (int)ft_strlen(*str);
	while ((tmp = ft_strstr(tmp, pattern)))
	{
		nb_occur++;
		tmp += pat_len;
	}
	if (pat_len < rep_len && !(*str = ft_memrealloc((void **)str, str_len, \
					str_len + ((rep_len - pat_len) * nb_occur) + 1)))
		return (NULL);
	tmp = *str;
	while ((tmp = ft_strstr(tmp, pattern)))
	{
		ft_memmove(tmp + rep_len, tmp + pat_len, ft_strlen(tmp) - pat_len + 1);
		ft_memmove(tmp, replacement, rep_len);
		tmp += rep_len;
	}
	return (*str);
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
		ft_printf("substitute to perform: %s by %s on %s\n", sub_list->rep, \
				sub_list->pat, str);
		if (!(new_cmd = ft_strreplace(&new_cmd, sub_list->pat, sub_list->rep)))
		{
			ft_printf("./21sh: cannot allocate memory\n");
			return (NULL);
		}
		sub_list = sub_list->next;
	}
	return (new_cmd);
}

void		fc_replace_last_hist(char *tmp)
{
	(void)tmp;
//	unsigned int	i;
//	unsigned int	save;
//
//	i = g_hist->used - 2;
//	save = i;
//	if (i <= 0)
//		return ;
//	while (i > 0 && g_hist->history_content[i])
//	{
//		ft_printf("hist: %s\n", g_hist->history_content + i);
//		i--;
//	}
//	g_hist->used = i;
//	while (i < save)
//	{
//		g_hist->history_content[i] = '\0';
//		i++;
//	}
//	g_hist->total_lines -= 1;
//	add_hentry(tmp, 1);
//	g_hist->used += 1;
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
	if (*args)
		tmp = prev_hist();
	while (sub_list->prev)
		sub_list = sub_list->prev;
	if (!(get_beg_matching_hist(&tmp, *args)))
	{
		ft_printf("tmp; %s\n", tmp);
		ft_printf("./21sh: fc: no command found\n");
		if (sub_list->pat)
			free_subsitute(sub_list);
		return (e_command_not_found);
	};
	ft_printf("matching hist: %s\n", tmp);
	if (!(tmp = fc_do_substitute(tmp, sub_list)))
		return (e_cannot_allocate_memory);
	free_subsitute(sub_list);
	ft_dprintf(STDERR_FILENO, "%s\n", tmp);
	/*
	fc_replace_last_hist(tmp);
	return (exec_input(tmp));*/
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
		ft_printf("please be patient it will come soon\n"); //status = exec_fc_other_opt(opt_list, args);
	return (0);
}
