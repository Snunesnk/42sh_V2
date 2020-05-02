/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_list_edit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:18:04 by snunes            #+#    #+#             */
/*   Updated: 2020/05/02 19:07:41 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_readline.h"
#include "shell.h"

static int	get_editor(char **editor, int opt_list)
{
	if (opt_list & FC_E_OPTION)
		*editor = ft_strdup(g_needed_arg);
	else if ((*editor = get_shell_var("FCEDIT", g_env)))
		*editor = ft_strdup(*editor);
	else if ((*editor = get_shell_var("EDITOR", g_env)))
		*editor = ft_strdup(*editor);
	else
		*editor = ft_strdup("vim");
	if (!*editor)
	{
		pbierror("cannot allocate memory");
		return (e_cannot_allocate_memory);
	}
	if (path_concat(editor, NULL, NULL, NULL) == e_command_not_found)
	{
		psherror(e_command_not_found, (g_needed_arg) ? g_needed_arg \
				: get_shell_var("FCEDIT", g_env), e_cmd_type);
		return (e_command_not_found);
	}
	return (e_success);
}

void		print_req_hist(int fd, int opt_list, int hist_beg, int hist_end)
{
	if (opt_list & FC_R_OPTION)
		swap_entries(&hist_end, &hist_beg);
	while (hist_beg < g_hist->nb_line)
		prev_hist();
	while (1)
	{
		if (!(opt_list & FC_N_OPTION))
			ft_dprintf(fd, "%d", g_hist->nb_line + 1);
		if (opt_list & FC_L_OPTION)
			ft_dprintf(fd, "\t");
		ft_dprintf(fd, "%s\n", g_hist->history_content + g_hist->offset \
				+ ((g_hist->offset == 0) ? 0 : 1));
		if (g_hist->nb_line == hist_end)
			break ;
		if (!(opt_list & FC_R_OPTION))
			next_hist();
		else
			prev_hist();
	}
	while (g_hist->nb_line < g_hist->total_lines)
		next_hist();
}

int			re_execute_cmd(int opt_list)
{
	int		fd;
	char	*command;
	char	*editor;

	editor = NULL;
	if ((fd = get_editor(&editor, opt_list)))
		return (fd);
	if (!(command = ft_strjoin(editor, " .monkeyshell_tmp_file")) \
			&& pbierror("cannot allocate memory"))
		return (e_cannot_allocate_memory);
	free(editor);
	exec_input(command);
	if ((fd = open(".monkeyshell_tmp_file", (O_RDONLY | O_CREAT), 0644)) < 0 \
			&& pbierror("cannot open temporary file"))
		return (1);
	while (get_next_line(fd, &command) > 0)
	{
		if (!add_pending_cmd(command))
			break ;
		free(command);
	}
	free(command);
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
		if ((fd = open(".monkeyshell_tmp_file", \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		{
			pbierror("cannot open temporary file");
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
	int		h_end;
	int		h_beg;

	h_end = -1;
	h_beg = -1;
	prev_hist();
	if (*args && g_hist->used != 0)
		get_hist_num(args, &opt_list, &h_end, &h_beg);
	else
	{
		h_end = g_hist->nb_line - 1;
		if ((h_beg = (opt_list & FC_L_OPTION) ? h_end - 15 : h_end) < 0)
			h_beg = 0;
	}
	if (h_end < 0 || h_beg < 0 || g_hist->total_lines == 1)
	{
		pbierror("history specification out of range");
		if (g_hist->total_lines != 1 && g_shell_is_interactive)
			fc_replace_last_hist(NULL);
		return (e_invalid_input);
	}
	if (get_fd_and_print(opt_list, h_beg, h_end))
		return ((opt_list & FC_L_OPTION) ? e_success : 1);
	(g_shell_is_interactive) ? fc_replace_last_hist(NULL) : rl_void();
	return (re_execute_cmd(opt_list));
}
