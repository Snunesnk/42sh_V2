/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:51 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 19:05:55 by snunes           ###   ########.fr       */
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

	if (g_back)
	{
		ft_bzero(g_line.line, g_line.len);
		prev = stack_pop_get_data(&g_back);
		ft_strcpy(g_line.line, prev->line);
		g_line.len = prev->len;
		g_line.c_pos = prev->size_buf;
		del_stat_line(prev);
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
