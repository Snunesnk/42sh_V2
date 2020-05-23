/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:51 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 16:46:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	paste_all_l(void)
{
	cursor_r();
	insert_text(g_clip.str, g_clip.l);
	cursor_l();
}

void	paste_all_r(void)
{
	insert_text(g_clip.str, g_clip.l);
	cursor_l();
}

void	undo_last(void)
{
	struct s_line_state	*prev;

	g_add_back_buf = 0;
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

void	undo_lastb(void)
{
	struct s_line_state	*prev;

	if (g_back)
	{
		ft_bzero(g_line.line, g_line.len);
		prev = stack_pop_get_data(&g_back);
		ft_strcpy(g_line.line, prev->line);
		g_line.len = prev->len;
		g_line.c_pos = 0;
		del_stat_line(prev);
		g_line.is_modified = 1;
	}
}

void	next_goto(void)
{
	if (g_last_goto_b)
	{
		g_got_input = 1;
		((void (*)(void))g_last_goto_b)();
		g_got_input = 0;
	}
}
