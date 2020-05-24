/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:20:55 by snunes            #+#    #+#             */
/*   Updated: 2020/05/24 14:37:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	vim_hist_up(void)
{
	history_up();
	if (!g_vim_cmd_count)
		return ;
	while (--g_vim_cmd_count > 0)
	{
		history_up();
		if (!g_hist.total_lines || g_hist.nb_line == 1)
			break ;
	}
	g_line.c_pos = 0;
}

void	vim_hist_down(void)
{
	history_down();
	if (!g_vim_cmd_count)
		return ;
	while (--g_vim_cmd_count > 0)
	{
		history_down();
		if (!g_hist.total_lines || g_hist.nb_line > g_hist.total_lines)
			break ;
	}
	g_line.c_pos = 0;
}

void	vim_cmd_cursor_r(void)
{
	cursor_r();
	if (!g_vim_cmd_count)
		return ;
	while (--g_vim_cmd_count > 0 && g_line.c_pos < g_line.len - 1)
		cursor_r();
}

void	vim_cmd_cursor_l(void)
{
	cursor_l();
	if (!g_vim_cmd_count)
		return ;
	while (--g_vim_cmd_count > 0 && g_line.c_pos > 0)
		cursor_l();
}

void	goto_first_non_blank(void)
{
	g_line.c_pos = 0;
	while (g_line.c_pos < g_line.len  - 1 \
			&& ft_isblank(g_line.line[g_line.c_pos]))
		g_line.c_pos++;
}
