/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:12:38 by snunes            #+#    #+#             */
/*   Updated: 2020/05/07 21:14:49 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_hist_compl(void)
{
	char			*hist_compl;
	unsigned int	offset_save;

	if (g_dumb_term)
		return ;
	if (ft_str_isspace(g_line.line) || !g_line.c_pos || !g_hist.total_lines)
		return ;
	offset_save = g_hist.offset;
	hist_compl = g_hist.history_content + g_hist.offset;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		insert_text(hist_compl + g_line.c_pos, ft_strlen(hist_compl + \
					g_line.c_pos));
	}
	while (g_hist.offset < offset_save)
		next_hist();
}

void	print_hist_compl(void)
{
	char			*hist_compl;
	unsigned int	offset_save;
	int				c_pos_save;

	if (g_hist.total_lines == 0 || g_dumb_term)
		return ;
	offset_save = g_hist.offset;
	hist_compl = g_hist.history_content + g_hist.offset + 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		c_pos_save = g_line.c_pos;
		place_cursor(g_line.len);
		ft_printf("%s%s%s", HIST_COMPL_COLOR, hist_compl + \
				g_line.len, END_OF_COLOR);
		place_cursor(c_pos_save);
	}
	while (g_hist.offset < offset_save)
		next_hist();
}

void	remove_completion(void)
{
	if (g_dumb_term)
		return ;
	place_cursor(g_line.len);
	ft_putstr(g_termcaps.clreol);
}
