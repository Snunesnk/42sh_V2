/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 14:32:31 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

static int	g_yank_cursor_move = 0;

void	cmaj_motion(void)
{
	ft_bzero(g_line.line + g_line.c_pos, g_line.len - g_line.c_pos);
	vim_insert();
	g_line.len = g_line.c_pos;
	g_line.is_modified = 1;
}

void	d_motion(union u_buffer d)
{
	union u_buffer	c;

	c.value = 0;
	c = read_key();
	if (c.value == d.value)
	{
		g_clip.l = g_line.len;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strdup(g_line.line);
		ft_bzero(g_line.line, g_line.len);
		g_line.len = 0;
		g_line.c_pos = 0;
		g_line.is_modified = 1;
	}
}

void	dmaj_motion(void)
{
	g_clip.l = g_line.len - g_line.c_pos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
	ft_bzero(&(g_line.line[g_line.c_pos]), g_clip.l);
	g_line.len -= g_clip.l;
	cursor_l();
	g_line.is_modified = 1;
}

void	yank_c(void)
{
	union u_buffer	c;
	static char		poss[] = " 0biFlW^$;EfTw|,Behty";
	int				ret;

	add_back();
	ret = g_line.c_pos;
	c = read_key();
	if (isctrlkey(c))
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
		return ;
	}
	if (!ft_strchr(poss, c.value))
		return ;
	if (c.value != 'y')
		(g_standard_keymap[c.value].func)(c.value);
	if (c.value == 'y')
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.l = g_line.len;
		g_clip.str = ft_strndup(g_line.line, g_line.len);
	}
	else if (ret < g_line.c_pos)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.l = g_line.c_pos - ret;
		g_clip.str = ft_strndup(g_line.line + ret, g_clip.l);
	}
	else
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.l = ret - g_line.c_pos;
		g_clip.str = ft_strndup(g_line.line + g_line.c_pos, g_clip.l);
	}
	if (!g_yank_cursor_move)
		g_line.c_pos = ret;
}

void	yank_eol(void)
{
	g_yank_cursor_move = 1;
	yank_c();
	g_yank_cursor_move = 0;
}
