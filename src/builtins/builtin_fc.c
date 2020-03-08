/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:16 by snunes            #+#    #+#             */
/*   Updated: 2020/03/08 22:10:37 by snunes           ###   ########.fr       */
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
	unsigned int	i;

	g_hist->offset = g_hist->used - 1;
	prev_hist();
	i = g_hist->offset;
	while (i < g_hist->used - 1)
	{
		g_hist->history_content[i] = '\0';
		i++;
	}
	g_hist->used = g_hist->offset + 1;
	if (tmp)
		add_hentry(tmp, 1);
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
			free_subsitute(sub_list);
		return (e_command_not_found);
	}
	if (!(tmp = fc_do_substitute(tmp, sub_list)))
		return (e_cannot_allocate_memory);
	free_subsitute(sub_list);
	ft_dprintf(STDERR_FILENO, "%s\n", tmp);
	fc_replace_last_hist(tmp);
	return (exec_input(tmp));
	return (1);
}

char		*get_editor(int opt_list, char **args)
{
	char	*editor;

	editor = NULL;
	if (opt_list & FC_E_OPTION)
	{
		editor = ft_strdup(*args);
		(*args)++;
	}
	else if ((editor = getenv("FCEDIT")))
		editor = ft_strdup(editor);
	else if ((editor = getenv("EDITOR")))
		editor = ft_strdup(editor);
	else
		editor = ft_strdup("vi");
	if (!(editor))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	return (editor);
}

void		get_hist_num(char **args, int opt_list, int *hist_end, int *hist_beg)
{
	char	*tmp;

	tmp = prev_hist();
	tmp = prev_hist();
	if (!(tmp = get_beg_matching_hist(&tmp, *args)))
		*hist_beg = -1;
	else
		*hist_beg = g_hist->nb_line;
	while (g_hist->nb_line != g_hist->total_lines)
		next_hist();
	(*args)++;
	if (*args)
	{
		if (!(tmp = get_beg_matching_hist(&tmp, *args)))
			*hist_end = -1;
		else
			*hist_end = g_hist->nb_line;
		while (g_hist->nb_line != g_hist->total_lines)
			next_hist();
	}
	else
		*hist_end = (opt_list & FC_L_OPTION) ? g_hist->total_lines - 1 : *hist_beg;
}

int			exec_fc_other_opt(int opt_list, char **args)
{
	char	*editor;
	int		fd;
	int		hist_end;
	int		hist_beg;

	if (g_hist->used == 0)
		return (0);
	if (!(editor = get_editor(opt_list, args)))
		return (e_cannot_allocate_memory);
	if (*args)
		get_hist_num(args, opt_list, &hist_end, &hist_beg);
	else
	{
		hist_end = g_hist->total_lines;
		hist_beg = (opt_list & FC_L_OPTION) ? hist_end - 16 : hist_end;
		if (hist_beg < 0)
			hist_beg = 0;
	}
	if (!(opt_list & FC_L_OPTION))
		fc_replace_last_hist(NULL);
	if (hist_end < 0 || hist_beg < 0)
	{
		ft_printf("./21sh: fc: history specification out of range\n");
		return (e_invalid_input);
	}
	if (hist_end < hist_beg)
	{
		int tmp;
		tmp = hist_end;
		hist_end = hist_beg;
		hist_beg = tmp;
		opt_list |= FC_R_OPTION;
	}
	if (opt_list & FC_L_OPTION)
		fd = STDOUT_FILENO;
	else
	{
		opt_list ^= FC_N_OPTION;
		if (!(fd = open(".21sh_tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0644)))
		{
			ft_printf("./21sh: cannot open temporary file\n");
			return (1);
		}
	}
	ft_printf("hist_end: %d, hist_beg: %d\n", hist_end, hist_beg);
	while (hist_beg > g_hist->nb_line)
		prev_hist();
	ft_printf("hist_end: %d, hist_beg: %d\n", hist_end, hist_beg);
	/*need to remove fc blah blah from hist*/
	while (hist_end > hist_beg)
	{
		if (opt_list & FC_N_OPTION)
			ft_dprintf(fd, "%d", g_hist->nb_line);
		if (opt_list & FC_L_OPTION)
			ft_dprintf(fd, "\t");
		ft_dprintf(fd, "%s\n", g_hist->history_content + g_hist->offset + 1);
		next_hist();
		hist_beg++;
	}
	ft_printf("hist_end: %d, hist_beg: %d\n", hist_end, hist_beg);
	if (opt_list & FC_L_OPTION)
		return (e_success);
	char	*command;
	if (!(command = ft_strjoin(editor, " .21sh_tmp_file")))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (e_cannot_allocate_memory);
	}
	free(editor);
	int	status;
	status = exec_input(command);
	/* need to midify hist, and then exec all the commands modified */
	return (status);
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
