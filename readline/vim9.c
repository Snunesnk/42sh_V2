/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim9.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:36:02 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 15:07:27 by abarthel         ###   ########.fr       */
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
	else if (ret == g_line.c_pos)
	{
		g_clip.l = 1;
		g_clip.str = ft_strndup(&g_line.line[ret], 1);
	}
	else
	{
		g_clip.l = ret - g_line.c_pos;
		g_clip.str = ft_strndup(g_line.line + g_line.c_pos, g_clip.l);
	}
}

void	inside_undo(void)
{
	struct s_line_state	*prev;

	if (g_back)
	{
		ft_memdel((void**)&g_line.line);
		prev = stack_pop_get_data(&g_back);
		g_line.line = prev->line;
		g_line.size_buf = prev->size_buf;
		g_line.c_pos = prev->c_pos;
		g_line.cursor_pos = prev->cursor_pos;
		g_line.len = prev->len;
		g_line.is_modified = prev->is_modified;
		ft_memdel((void**)&prev);
	}
	else
	{
		ft_bzero(g_line.line, g_line.len);
		g_line.c_pos = 0;
		g_line.cursor_pos = 0;
		g_line.len = 0;
		g_line.is_modified = 1;
	}
}
