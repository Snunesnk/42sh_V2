/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:14:05 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:38:06 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	cursor_u(void)
{
	if (g_cursor.v_pos != 0)
	{
		if (g_cursor.v_pos == 1 && g_cursor.c_pos < g_dis.prompt_l)
		{
			ft_putstr(tgoto(g_termcaps.ch, 0, g_dis.prompt_l));
			g_dis.cbpos = 0;
		}
		else
			g_dis.cbpos -= g_sc.w;
		--g_cursor.v_pos;
		ft_putstr(tgoto(g_termcaps.up, 0, 0));
		update_line();
	}
}

void	clear_line(void)
{
	rl_home();
	ft_putstr(g_termcaps.clreol);
	g_line.len = 0;
	ft_bzero(g_line.line, g_line.size_buf);
}

void	rl_home(void)
{
	g_cursor.c_pos = g_dis.prompt_l;
	if (g_cursor.c_pos > 0)
		ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
	if (g_cursor.v_pos > 0)
	{
		ft_putstr(tgoto(g_termcaps.gup, 0, g_cursor.v_pos));
		g_cursor.v_pos = 0;
	}
	g_dis.cbpos = 0;
	update_line();
}

void	rl_end(void)
{
	g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
	if (g_cursor.c_pos > 0)
	{
		ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		g_dis.cbpos = g_line.len;
	}
	if (g_cursor.v_pos != g_dis.botl)
	{
		ft_putstr(tgoto(g_termcaps.gdo, 0, g_dis.botl - g_cursor.v_pos));
		g_dis.cbpos = g_line.len;
		g_cursor.v_pos = (g_dis.prompt_l + g_dis.cbpos) / g_sc.w;
	}
	update_line();
}

void	wd_right(void)
{
	while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
	while (g_line.line[g_dis.cbpos] != ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
}
