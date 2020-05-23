/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:51 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 18:42:02 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	paste_all_l(void)
{
	cursor_r();
	if (g_vim_cmd_count == 0)
		++g_vim_cmd_count;
	if (g_clip.str && g_clip.l)
	{
		while (g_vim_cmd_count > 0)
		{
			insert_text(g_clip.str, g_clip.l);
			--g_vim_cmd_count;
		}
		cursor_l();
	}
}

void	paste_all_r(void)
{
	if (g_vim_cmd_count == 0)
		++g_vim_cmd_count;
	if (g_clip.str && g_clip.l)
	{
		while (g_vim_cmd_count > 0)
		{
			insert_text(g_clip.str, g_clip.l);
			--g_vim_cmd_count;
		}
		cursor_l();
	}
}

void	undo_last(void)
{
	struct s_line_state	*prev;

	g_add_back_buf = 0;
	if (g_vim_cmd_count == 0)
		++g_vim_cmd_count;
	while (g_vim_cmd_count > 0)
	{
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
		--g_vim_cmd_count;
	}
}

void	undo_lastb(void)
{
	struct s_line_state	*prev;

	g_vim_cmd_count = 0;
	while (g_back && g_back->previous)
		stack_pop(&g_back, del_stat_line);
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
