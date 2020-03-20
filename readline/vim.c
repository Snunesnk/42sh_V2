#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	replace_text(const char *string, int len)
{
	int nlen;

	nlen = g_dis.cbpos + len;
	while (nlen >= g_line.size_buf)
		l_expand();
	ft_strncpy(&g_line.line[g_dis.cbpos], string, len);
	if (nlen > g_line.len)
		g_line.len = nlen;
	g_dis.cbpos += len;
	update_line();	
}


void	vim_hash(void)
{
	g_input_break = 1;
	g_dis.cbpos = 0;
	insert_text("#", 1);
}

void	call_fc(void)
{ /* Need some help from Simon to better implement this */
//	return ; /* If no history */
	char *argv[2];

	argv[0] = "fc";
	argv[1] = NULL;
	cmd_fc(1, argv);
}

void	beg_next_wd(void)
{
	while (g_line.line[g_dis.cbpos] != ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
	while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
}

void	beg_next_alnum(void)
{
	if (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
			cursor_r();
		while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
			cursor_r();
	}
	else if (!ft_isalnum(g_line.line[g_dis.cbpos])&& g_dis.cbpos < g_line.len)
		while (!ft_isalnum(g_line.line[g_dis.cbpos])&& g_dis.cbpos < g_line.len)
			cursor_r();
}

void	end_next_alnum(void)
{
	if (g_dis.cbpos < g_line.len)
			cursor_r();
	if (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		while (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
			cursor_r();
	if (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_dis.cbpos + 1]) && g_dis.cbpos + 1 < g_line.len)
			cursor_r();
	}
	else if (ft_ispunct(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_ispunct(g_line.line[g_dis.cbpos + 1]) && g_dis.cbpos + 1 < g_line.len)
			cursor_r();
	}
}

void	end_next_wd(void)
{
	if (ft_isspace(g_line.line[g_dis.cbpos + 1]))
		cursor_r();
	while (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		cursor_r();
	while (!ft_isspace(g_line.line[g_dis.cbpos + 1]) && g_dis.cbpos + 1 < g_line.len)
		cursor_r();
}

void	beg_last_alnum(void)
{
	if (g_dis.cbpos > 0)
		cursor_l();
	if (g_dis.cbpos > 0 && ft_isspace(g_line.line[g_dis.cbpos]))
		while (g_dis.cbpos > 0 && ft_isspace(g_line.line[g_dis.cbpos]))
			cursor_l();
	if (g_dis.cbpos > 0 && ft_isalnum(g_line.line[g_dis.cbpos]))
	{
		while (g_dis.cbpos > 0 && ft_isalnum(g_line.line[g_dis.cbpos - 1]))
			cursor_l();
	}
	else if (g_dis.cbpos > 0 && ft_ispunct(g_line.line[g_dis.cbpos]))
	{
		while (g_dis.cbpos > 0 && ft_ispunct(g_line.line[g_dis.cbpos - 1]))
			cursor_l();
	}
}

void	goto_chr_right(void)
{
	int		p;
	static int	c;

	if (!g_got_input)
	{
		g_last_goto_f = goto_chr_right;
		c = 0;
		read(STDIN_FILENO, &c, sizeof(int));
	}
	p = g_dis.cbpos;
	if (ft_isprint(c))
	{
		while (p < g_line.len)
		{
			if (g_line.line[p] == c)
			{
				g_dis.cbpos = p;
				update_line();
				return ;
			}
			++p;
		}
	}
}

void	goto_chr_left(void)
{
	int		p;
	static int	c;

	if (!g_got_input)
	{
		g_last_goto_f = goto_chr_left;
		c = 0;
		read(STDIN_FILENO, &c, sizeof(int));
	}
	p = g_dis.cbpos;
	if (ft_isprint(c))
	{
		while (p >=  0)
		{
			if (g_line.line[p] == c)
			{
				g_dis.cbpos = p;
				update_line();
				return ;
			}
			--p;
		}
	}
}

void	goto_pchr_left(void)
{
	int		p;
	static int	c;

	if (!g_got_input)
	{
		g_last_goto_f = goto_pchr_left;
		c = 0;
		read(STDIN_FILENO, &c, sizeof(int));
	}
	p = g_dis.cbpos;
	if (ft_isprint(c))
	{
		while (p - 1 >=  0)
		{
			if (g_line.line[p - 1] == c)
			{
				g_dis.cbpos = p;
				update_line();
				return ;
			}
			--p;
		}
	}
}

void	goto_pchr_right(void)
{
	int		p;
	static int	c;

	if (!g_got_input)
	{
		g_last_goto_f = goto_pchr_right;
		c = 0;
		read(STDIN_FILENO, &c, sizeof(int));
	}
	p = g_dis.cbpos;
	if (ft_isprint(c))
	{
		while (p + 1 < g_line.len)
		{
			if (g_line.line[p + 1] == c)
			{
				g_dis.cbpos = p;
				update_line();
				return ;
			}
			++p;
		}
	}
}

void	last_goto(void)
{
	if (g_last_goto_f)
	{
		g_got_input = 1;
		((void (*)(void))g_last_goto_f)();
		g_got_input = 0;
	}
}

void	insert_mode_next(void)
{
	cursor_r();
	vim_insert();
}

void	insert_mode_last(void)
{
	g_dis.cbpos = g_line.len;
	vim_insert();
	update_line();
}

void	insert_mode_first(void)
{
	g_dis.cbpos = 0;
	vim_insert();
	update_line();
}

void	replace_wd(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, sizeof(int));
	if (ft_isprint(c))
	{
		g_line.line[g_dis.cbpos] = c;
		update_line();
	}
}

void	replace_mode(void)
{
	vim_insert();
	g_replace_mode = 1;
}

void	clear_all_l(void)
{
	ft_bzero(g_line.line, g_line.len);
	g_dis.cbpos = 0;
	update_line();
	vim_insert();
}

void	c_motion(union u_buffer d)
{
	union u_buffer c;

	c.value = 0;
	read(STDIN_FILENO, c.buf, sizeof(int));
	if (c.value == d.value)
		clear_all_l();
}

void	cmaj_motion(void)
{
	ft_bzero(&g_line.line[g_dis.cbpos], g_line.len - g_dis.cbpos);
	update_line();
	vim_insert();
}

void	d_motion(union u_buffer d)
{
	union u_buffer c;

	c.value = 0;
	read(STDIN_FILENO, c.buf, sizeof(int));
	if (c.value == d.value)
	{
		g_clip.l = g_line.len;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strdup(g_line.line);
		ft_bzero(g_line.line, g_line.len);
		g_dis.cbpos = 0;
		update_line();
	}
}

void	dmaj_motion(void)
{
	g_clip.l = g_line.len - g_dis.cbpos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
	ft_bzero(&(g_line.line[g_dis.cbpos]), g_clip.l);
	g_line.len -= g_clip.l;
	cursor_l();
	update_line();
}

void	yank_c(void)
{
	g_clip.l = 1;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
}

void	yank_eol(void)
{
	g_clip.l = g_line.len - g_dis.cbpos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
}

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

void	undo_lastB(void)
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
