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
		g_dis.cbpos = prev->size_buf;
		del_stat_line(prev);
		update_line();
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
		g_dis.cbpos = 0;
		del_stat_line(prev);
		update_line();
	}
}
