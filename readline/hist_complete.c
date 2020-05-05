/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:12:38 by snunes            #+#    #+#             */
/*   Updated: 2020/05/05 20:07:43 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_hist_compl(void)
{
	char			*hist_compl;
	unsigned int	offset_save;

	if (ft_str_isspace(g_line.line) || !g_dis.cbpos || !g_hist.total_lines)
		return ;
	offset_save = g_hist.offset;
	hist_compl = g_hist.history_content + g_hist.offset;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		insert_text(hist_compl + g_dis.cbpos, ft_strlen(hist_compl + \
					g_dis.cbpos));
	}
	while (g_hist.offset < offset_save)
		next_hist();
}

void	go_up(int start_col, char *str)
{
	int	i;
	int	col;
	int	up;

	i = 0;
	col = start_col;
	up = 0;
	while (str[i])
	{
		if (col == g_sc.w)
		{
			col = 0;
			up++;
		}
		if (str[i] == '\n')
		{
			col = 0;
			up++;
		}
		i++;
		col++;
	}
	if (up)
		ft_putstr(tgoto(g_termcaps.gup, 0, up));
}

void	print_hist_compl(void)
{
	char			*hist_compl;
	unsigned int	offset_save;
	int				len;
	int				start_col;

	if (g_hist.total_lines == 0)
		return ;
	offset_save = g_hist.offset;
	hist_compl = g_hist.history_content + g_hist.offset + 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		len = g_line.len - g_dis.cbpos;
		start_col = (g_dis.start_offset + g_dis.prompt_l + g_dis.cbpos) \
					% g_sc.w;
		while (len--)
			ft_putstr(g_termcaps.forward_char);
		ft_printf("%s%s%s", HIST_COMPL_COLOR, hist_compl + \
				g_line.len, END_OF_COLOR);
		ft_strlen(hist_compl + g_line.len);
		ft_putstr(tgoto(g_termcaps.ch, 0, start_col));
		go_up(start_col, hist_compl + g_dis.cbpos);
	}
	while (g_hist.offset < offset_save)
		next_hist();
}

void	remove_completion(void)
{
	while (g_dis.cbpos < g_line.len)
		cursor_r();
	ft_putstr(g_termcaps.clreol);
}
