/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:12:38 by snunes            #+#    #+#             */
/*   Updated: 2020/04/29 19:09:25 by snunes           ###   ########.fr       */
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

void	print_hist_compl(void)
{
	char				*hist_compl;
	unsigned int		offset_save;
	int					len;

	len = 0;
	offset_save = g_hist->offset;
	hist_compl = g_hist->history_content + g_hist->offset;
	if (g_hist->offset != 0)
		hist_compl += 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		while (g_dis.cbpos + len < g_line.len)
		{
			ft_putstr(g_termcaps.forward_char);
			len++;
		}
		ft_printf("%s%s%s", HIST_COMPL_COLOR, hist_compl + \
				g_line.len, END_OF_COLOR);
		len += ft_strlen(hist_compl + g_line.len);
		while (len--)
			ft_putstr(g_termcaps.backspace);
	}
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
