/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:12:38 by snunes            #+#    #+#             */
/*   Updated: 2020/04/29 23:24:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_hist_compl(void)
{
	char				*hist_compl;
	unsigned int		offset_save;

	offset_save = g_hist->offset;
	hist_compl = g_hist->history_content + g_hist->offset;
	if (g_hist->offset != 0)
		hist_compl += 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		insert_text(hist_compl + g_dis.cbpos, ft_strlen(hist_compl + \
					g_dis.cbpos));
	}
	while (g_hist->offset < offset_save)
		next_hist();
}


static void	real_print_hist_compl(char *hist_compl)
{
	int	len;
	int	line;
	int	start_col;

	len = g_line.len - g_dis.cbpos;
	start_col = (g_dis.start_offset + g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
	line = (start_col + ft_strlen(hist_compl + g_dis.cbpos)) / g_sc.w;
	while (len--)
		ft_putstr(g_termcaps.forward_char);
	ft_printf("%s%s%s", HIST_COMPL_COLOR, hist_compl + \
			g_line.len, END_OF_COLOR);
	ft_strlen(hist_compl + g_line.len);
	ft_putstr(tgoto(g_termcaps.ch, 0, start_col));
	if (line)
		ft_putstr(tgoto(g_termcaps.gup, 0, line));
}

void	print_hist_compl(void)
{
	char				*hist_compl;
	unsigned int		offset_save;

	offset_save = g_hist->offset;
	hist_compl = g_hist->history_content + g_hist->offset;
	if (g_hist->offset != 0)
		hist_compl += 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
		real_print_hist_compl(hist_compl);
	while (g_hist->offset < offset_save)
		next_hist();
}

void	remove_completion(void)
{
	int	len;

	len = 0;
	while (g_dis.cbpos < g_line.len)
	{
		cursor_r();
		len++;
	}
	ft_putstr(g_termcaps.clreol);
	while (len--)
		cursor_l();
}
