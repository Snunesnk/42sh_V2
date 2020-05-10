/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:14:05 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 22:50:13 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	cursor_u(void)
{
	if ((g_line.c_pos + g_dis.start_offset) / (g_sc.w) > 0)
	{
		g_line.c_pos -= g_sc.w;
		if (g_line.c_pos < 0)
			g_line.c_pos = 0;
	}
}

void	clear_line(void)
{
	place_cursor(0);
	ft_bzero(g_line.line, g_line.size_buf);
	g_line.len = 0;
	g_line.c_pos = 0;
	g_line.is_modified = 1;
	update_line();
}

void	rl_home(void)
{
	place_cursor(0);
}

void	rl_end(void)
{
	place_cursor(g_line.len);
}

void	wd_right(void)
{
	while (g_line.line[g_line.c_pos] == ' ' && g_line.c_pos < g_line.len)
		cursor_r();
	while (g_line.line[g_line.c_pos] != ' ' && g_line.c_pos < g_line.len)
		cursor_r();
}
