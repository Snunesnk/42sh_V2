/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:13:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:39:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	wd_left(void)
{
	while (g_dis.cbpos > 0 && g_line.line[g_dis.cbpos - 1] == ' ')
		cursor_l();
	while (g_dis.cbpos > 0 && g_line.line[g_dis.cbpos - 1] != ' ')
		cursor_l();
}

void	clear_scr(void)
{
	ft_putstr(g_termcaps.clrpag);
	update_line();
}

void	rl_void(void)
{
	ft_putstr(g_termcaps.bl);
}

void	paste_via_input(unsigned long v)
{
	union u_buffer	u;
	int				len;

	len = 0;
	u.value = v;
	while (len < 8 && u.buf[len])
		++len;
	insert_text(&(u.buf[0]), len);
}

void	clear_eol(void)
{
	if (g_dis.cbpos != g_line.len)
	{
		g_clip.l = g_line.len - g_dis.cbpos;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
		ft_bzero(&(g_line.line[g_dis.cbpos]), g_clip.l);
		g_line.len -= g_clip.l;
		update_line();
	}
}
