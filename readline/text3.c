/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:14:05 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/13 16:15:50 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	cursor_u(void)
{
	int	c_pos;
	int	v_pos;
	int	start_v_pos;
	int	start_c_pos;

	calc_dcursor(g_line.c_pos, &v_pos, &c_pos);
	start_c_pos = c_pos;
	start_v_pos = v_pos;
	if (v_pos == g_dis.start_line)
		return ;
	while (g_line.c_pos && (start_v_pos == v_pos || c_pos > start_c_pos))
	{
		g_line.c_pos -= 1;
		calc_dcursor(g_line.c_pos, &v_pos, &c_pos);
		if (start_v_pos - v_pos >= 2)
		{
			g_line.c_pos--;
			break ;
		}
	}
}

void	clear_line(void)
{
	place_cursor(0);
	ft_bzero(g_line.line, g_line.size_buf);
	g_line.len = 0;
	g_line.c_pos = 0;
	g_line.is_modified = 1;
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
