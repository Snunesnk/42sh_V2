/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/25 13:36:32 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

static int	g_yank_cursor_move = 0;

void	cmaj_motion(void)
{
	add_back();
	del_from_to(g_line.c_pos, g_line.len, NO_SAVE);
	vim_insert();
}

void	d_motion(void)
{
	union u_buffer	c;
	static char		poss[] = " 0biFlW^$;EfTw|,Behtd";
	int				ret;

	ret = g_line.c_pos;
	c.value = 0;
	if (read(STDIN_FILENO, c.buf, sizeof(int)) < 0)
		return ;
	if (!ft_strchr(poss, c.value))
		return ;
	if (c.value != 'd')
		(g_standard_keymap[c.value].func)(c.value);
	else
	{
		del_from_to(0, g_line.len, SAVE);
		return ;
	}
	add_back();
	if (ret < g_line.c_pos)
		del_from_to(ret, g_line.c_pos, SAVE);
	else
		del_from_to(g_line.c_pos, ret, NO_SAVE);
}

void	dmaj_motion(void)
{
	add_back();
	del_from_to(g_line.c_pos, g_line.len, SAVE);
	cursor_l();
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
		return (arrow_yank(c));
	if (!ft_strchr(poss, c.value))
		return ;
	if (c.value != 'y')
		(g_standard_keymap[c.value].func)(c.value);
	if (g_clip.str != NULL)
		free(g_clip.str);
	update_clipboard(ret, c.value);
	if (!g_yank_cursor_move)
		g_line.c_pos = ret;
}

void	yank_eol(void)
{
	g_yank_cursor_move = 1;
	yank_c();
	g_yank_cursor_move = 0;
}
