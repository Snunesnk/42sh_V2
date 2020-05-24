/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim9.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:36:02 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 14:41:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	arrow_yank(union u_buffer c)
{
	if (c.buf[2] == 67)
	{
		clear_eol();
		vim_insert();
	}
	else if (c.buf[2] == 68)
	{
		clear_eol();
		cursor_l();
	}
	else if (c.buf[2] == 65)
	{
		rl_end();
		vim_insert();
	}
	else if (c.buf[2] == 66)
		rl_home();

}

void	update_clipboard(int ret, int c)
{
	if (c == 'y')
	{
		g_clip.l = g_line.len;
		g_clip.str = ft_strndup(g_line.line, g_line.len);
	}
	else if (ret < g_line.c_pos)
	{
		g_clip.l = g_line.c_pos - ret;
		g_clip.str = ft_strndup(g_line.line + ret, g_clip.l);
	}
	else
	{
		g_clip.l = ret - g_line.c_pos;
		g_clip.str = ft_strndup(g_line.line + g_line.c_pos, g_clip.l);
	}
}
