/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_list_edit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:18:04 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 16:08:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_readline.h"

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
	int		sign;

	sign = (**args == '-') ? -1 : 1;
	if (sign < 0)
		*args += 1;
	tmp = prev_hist();
	tmp = prev_hist();
	if (!(get_beg_matching_hist(&tmp, *args)))
		*hist_beg = -1;
	else
		*hist_beg = g_hist->nb_line;
	while (g_hist->nb_line < g_hist->total_lines)
		next_hist();
	args += 1;
	if (*args)
	{
		if (!(get_beg_matching_hist(&tmp, *args)))
			*hist_end = -1;
		else
			*hist_end = g_hist->nb_line;
		while (g_hist->nb_line < g_hist->total_lines)
			next_hist();
	}
	else
		*hist_end = (opt_list & FC_L_OPTION) ? g_hist->total_lines - 1 : *hist_beg;
}

void		print_req_hist(int fd, int opt_list, int hist_beg, int hist_end)
{
	prev_hist();
	prev_hist();
	while (!(opt_list & FC_R_OPTION) && hist_beg < g_hist->nb_line)
		prev_hist();
	while (hist_end >= g_hist->nb_line \
			&& g_hist->nb_line < g_hist->total_lines - 1\
			&& !(opt_list & FC_R_OPTION))
	{
		if (!(opt_list & FC_N_OPTION))
			ft_dprintf(fd, "%d", g_hist->nb_line);
		if (opt_list & FC_L_OPTION)
			ft_dprintf(fd, "\t");
		ft_dprintf(fd, "%s\n", g_hist->history_content + g_hist->offset + 1);
		next_hist();
	}
	while (hist_beg <= g_hist->nb_line && (opt_list & FC_R_OPTION))
	{
		if (!(opt_list & FC_N_OPTION))
			ft_dprintf(fd, "%d", g_hist->nb_line);
		if (opt_list & FC_L_OPTION)
			ft_dprintf(fd, "\t");
		ft_dprintf(fd, "%s\n", g_hist->history_content + g_hist->offset + 1);
		prev_hist();
	}
	while (g_hist->nb_line < g_hist->total_lines)
		next_hist();
}

int			exec_fc_other_opt(int opt_list, char **args)
{
	char	*editor;
	int		fd;
	int		hist_end;
	int		hist_beg;
	int		status;

	status = 0;
	if (g_hist->used == 0)
		return (0);
	if (!(editor = get_editor(opt_list, args)))
		return (e_cannot_allocate_memory);
	if (*args)
		get_hist_num(args, opt_list, &hist_end, &hist_beg);
	else
	{
		hist_end = g_hist->total_lines - 1;
		hist_beg = (opt_list & FC_L_OPTION) ? hist_end - 16 : hist_end;
		if (hist_beg < 0)
			hist_beg = 0;
	}
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
		opt_list |= FC_N_OPTION;
		if ((fd = open(".21sh_tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		{
			ft_printf("./21sh: cannot open temporary file\n");
			return (1);
		}
	}
	print_req_hist(fd, opt_list, hist_beg, hist_end);
	if (fd != STDOUT_FILENO)
		close(fd);
	if (opt_list & FC_L_OPTION)
		return (e_success);
	fc_replace_last_hist(NULL);
	char	*command;
	if (!(command = ft_strjoin(editor, " .21sh_tmp_file")))
	{
		ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n");
		return (e_cannot_allocate_memory);
	}
	free(editor);
	status = exec_input(command);
	command = NULL;
	if ((fd = open(".21sh_tmp_file", (O_RDONLY | O_CREAT), 0644)) < 0)
	{
		ft_printf("./21sh: cannot open temporary file\n");
		return (1);
	}
	while ((status = get_next_line(fd, &command)) > 0)
	{
		ft_dprintf(STDERR_FILENO, "%s", command);
		add_hentry(command, 1);
		exec_input(command);
		command = NULL;
	}
	close(fd);
	return (status);
}