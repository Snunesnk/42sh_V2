/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:20:55 by snunes            #+#    #+#             */
/*   Updated: 2020/05/23 15:49:43 by snunes           ###   ########.fr       */
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
