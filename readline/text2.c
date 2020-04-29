/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:14:17 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 18:30:37 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	kill_line(void)
{
	write(STDOUT_FILENO, "^C", STDERR_FILENO);
	ft_bzero(g_line.line, g_line.size_buf);
	g_dis.cbpos = 0;
	g_line.len = 0;
	g_cursor.c_pos = 0;
	if (g_cursor.v_pos != g_dis.botl)
		ft_putstr(tgoto(g_termcaps.gdo, 0, g_dis.botl - g_cursor.v_pos));
	g_cursor.v_pos = 0;
	if (g_subprompt)
		g_input_break = 1;
	else
	{
		write(STDOUT_FILENO, "\n", STDOUT_FILENO);
		update_line();
	}
}

void	rl_insert(int c)
{
	char s[1];

	s[0] = (char)c;
	insert_text(s, 1);
}

void	cursor_l(void)
{
	if (g_dis.cbpos > 0)
	{
		if (g_cursor.c_pos > 0)
		{
			ft_putstr(tgoto(g_termcaps.backspace, 0, 0));
			--g_cursor.c_pos;
		}
		else
		{
			g_cursor.c_pos = g_sc.w - 1;
			--g_cursor.v_pos;
			ft_putstr(tgoto(g_termcaps.up, 0, 0));
			ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		}
		g_dis.cbpos -= 1;
	}
}

void	cursor_r(void)
{
	if (g_dis.cbpos < g_line.len)
	{
		if (g_cursor.c_pos == g_sc.w)
		{
			g_cursor.c_pos = 0;
			++g_cursor.v_pos;
			ft_putstr(tgoto(g_termcaps.do1, 0, 0));
			ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		}
		else
		{
			++g_cursor.c_pos;
			ft_putstr(tgoto(g_termcaps.forward_char, 0, 0));
		}
		g_dis.cbpos += 1;
	}
	else
		insert_hist_compl();
}

void	cursor_d(void)
{
	int len_last_line;

	if (g_cursor.v_pos != g_dis.botl)
	{
		len_last_line = (g_dis.prompt_l + g_line.len) % g_sc.w;
		if (g_cursor.v_pos == g_dis.botl - 1
				&& g_cursor.c_pos > len_last_line)
		{
			ft_putstr(tgoto(g_termcaps.ch, 0, len_last_line));
			g_dis.cbpos = g_line.len;
		}
		else
			g_dis.cbpos += g_sc.w;
		++g_cursor.v_pos;
		ft_putstr(tgoto(g_termcaps.do1, 0, 0));
		update_line();
	}
}
