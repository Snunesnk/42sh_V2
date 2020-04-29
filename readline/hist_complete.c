/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:12:38 by snunes            #+#    #+#             */
/*   Updated: 2020/04/29 14:51:30 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	insert_hist_compl(void)
{
	char				*hist_compl;
	int					pos_save;
	unsigned int		offset_save;

	return ;
	offset_save = g_hist->offset;
	pos_save = g_dis.cbpos;
	hist_compl = g_hist->history_content + g_hist->offset;
	ft_printf("hist_compl: %s\n", hist_compl);
	if (g_hist->offset != 0)
		hist_compl += 1;
	hist_compl = get_beg_matching_hist(&hist_compl, g_line.line);
	if (hist_compl)
	{
		insert_text(HIST_COMPL_COLOR, ft_strlen(HIST_COMPL_COLOR));
		insert_text(hist_compl + g_dis.cbpos - 1, ft_strlen(hist_compl + g_dis.cbpos - 1));
		insert_text("\033[0m", 4);
		while (g_dis.cbpos != pos_save)
			cursor_l();
	}
	while (g_hist->offset != offset_save)
		next_hist();

}

void	remove_hist_compl(void)
{
	int	i;
	int	pos_save;

	pos_save = g_dis.cbpos;
	i = g_line.len - ft_strlen(HIST_COMPL_COLOR);
	while (i > 0 && !ft_strnequ(HIST_COMPL_COLOR, g_line.line + i, \
				ft_strlen(HIST_COMPL_COLOR)))
		i--;
	if (!ft_strnequ(HIST_COMPL_COLOR, g_line.line + i, \
				ft_strlen(HIST_COMPL_COLOR)))
		return ;
	while (g_dis.cbpos != i)
		cursor_r();
	while (g_dis.cbpos != g_line.len)
		rl_delete();
	while (g_dis.cbpos != pos_save)
		cursor_l();
}
