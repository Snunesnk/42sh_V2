/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_list_edit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:18:04 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 22:21:25 by snunes           ###   ########.fr       */
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

void		print_req_hist(int fd, int opt_list, int hist_beg, int hist_end)
{
	while (!(opt_list & FC_R_OPTION) && hist_beg < g_hist->nb_line)
		prev_hist();
	while ((opt_list & FC_R_OPTION) && hist_end < g_hist->nb_line)
		prev_hist();
	while ((g_hist->nb_line <= hist_end && !(opt_list & FC_R_OPTION)) \
			|| (g_hist->nb_line >= hist_beg && (opt_list & FC_R_OPTION)))
	{
		if (!(opt_list & FC_N_OPTION))
			ft_dprintf(fd, "%d", g_hist->nb_line);
		if (opt_list & FC_L_OPTION)
			ft_dprintf(fd, "\t");
		ft_dprintf(fd, "%s\n", g_hist->history_content + g_hist->offset + 1);
		if (!(opt_list & FC_R_OPTION))
			next_hist();
		else
			prev_hist();
	}
	while (g_hist->nb_line < g_hist->total_lines)
		next_hist();
}

int			re_execute_cmd(int opt_list, char **args)
{
	int		fd;
	char	*command;
	char	*editor;

	command = NULL;
	if (!(editor = get_editor(opt_list, args)))
		return (e_cannot_allocate_memory);
	if (!(command = ft_strjoin(editor, " .21sh_tmp_file")) \
			&& ft_dprintf(STDERR_FILENO, "./21sh: cannot allocate memory\n"))
		return (e_cannot_allocate_memory);
	free(editor);
	exec_input(command);
	if ((fd = open(".21sh_tmp_file", (O_RDONLY | O_CREAT), 0644)) < 0 \
			&& ft_printf("./21sh: cannot open temporary file\n"))
		return (1);
	while (get_next_line(fd, &command) > 0)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", command);
		add_hentry(command, 1);
		exec_input(command);
		command = NULL;
	}
	close(fd);
	return (e_success);
}

int			get_fd_and_print(int opt_list, int hist_beg, int hist_end)
{
	int		fd;

	if (opt_list & FC_L_OPTION)
		fd = STDOUT_FILENO;
	else
	{
		opt_list |= FC_N_OPTION;
		if ((fd = open(".21sh_tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644)) \
				< 0)
		{
			ft_printf("./21sh: cannot open temporary file\n");
			return (1);
		}
	}
	print_req_hist(fd, opt_list, hist_beg, hist_end);
	if (fd != STDOUT_FILENO)
		close(fd);
	if (opt_list & FC_L_OPTION)
		return (1);
	return (0);
}

int			exec_fc_other_opt(int opt_list, char **args)
{
	int		hist_end;
	int		hist_beg;

	hist_end = -1;
	hist_beg = -1;
	if (g_hist->used == 0)
		return (0);
	if (*args)
		get_hist_num(args, opt_list, &hist_end, &hist_beg);
	else
	{
		hist_end = g_hist->total_lines - 2;
		hist_beg = (opt_list & FC_L_OPTION) ? hist_end - 16 : hist_end;
		if (hist_beg < 0)
			hist_beg = 0;
	}
	if (hist_end < 0 || hist_beg < 0)
	{
		ft_printf("./21sh: fc: history specification out of range\n");
		return (e_invalid_input);
	}
	if (get_fd_and_print(opt_list, hist_beg, hist_end))
		return ((opt_list & FC_L_OPTION) ? e_success : 1);
	fc_replace_last_hist(NULL);
	return (re_execute_cmd(opt_list, args));
}
