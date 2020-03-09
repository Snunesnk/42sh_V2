#include "ft_readline.h"

struct s_clipboard g_clip = { .str = NULL, .l = 0 };
char *g_original_cmd;
int g_full_completion = 1;

void init_line_buffer(void)
{
	g_line.size_buf = 512;
	g_line.line = (char*)malloc(sizeof(char) * g_line.size_buf);
	ft_bzero(g_line.line, g_line.size_buf);
	g_dis.cbpos = 0;
	g_line.len = 0;
}

static void l_expand(void)
{
	char *new;
	size_t lold;

	lold = g_line.size_buf;
	g_line.size_buf = lold * 2;
	new = (char*)malloc(sizeof(char) * g_line.size_buf);
	ft_bzero(new, lold * 2);
	ft_strncpy(new, g_line.line, lold);
	free(g_line.line);
	g_line.line = new;
}

void insert_text(const char *string, int len)
{
	while (len + g_line.len >= g_line.size_buf)
		l_expand();
	if (g_dis.cbpos < g_line.len)
	{
		ft_memmove(&(g_line.line[g_dis.cbpos + len]),
				&(g_line.line[g_dis.cbpos]),
				g_line.len - g_dis.cbpos);
	}
	ft_memmove(&(g_line.line[g_dis.cbpos]), string, len);
	g_line.len += len;
	g_dis.cbpos += len;
	update_line();
}

void rl_delete(void)
{
	if (g_dis.cbpos < g_line.len && g_line.len > 0)
	{
		if (g_line.line[g_dis.cbpos] && g_dis.cbpos <= g_line.len)
		{
			ft_memmove(&(g_line.line[g_dis.cbpos]),
	&(g_line.line[g_dis.cbpos + 1]), g_line.len - g_dis.cbpos + 1);
			g_line.line[g_line.len + 1] = '\0';
			update_line();
			--g_line.len;
		}
		else if (g_dis.cbpos > 0)
		{
			g_line.line[g_dis.cbpos] = '\0';
			update_line();
			--g_line.len;
		}
	}
}

void rl_backspace(void)
{
	if (g_dis.cbpos > 0)
	{
		cursor_l();
		if (g_line.line[g_dis.cbpos])
		{
			ft_memmove(&(g_line.line[g_dis.cbpos]),
	&(g_line.line[g_dis.cbpos + 1]), g_line.len - g_dis.cbpos + 1);
			g_line.line[g_line.len + 1] = '\0';
		}
		else
			g_line.line[g_dis.cbpos] = '\0';
		--g_line.len;
		update_line();
	}
}

void kill_line(void)
{
	write(STDOUT_FILENO, "^C", 2);
	ft_bzero(g_line.line, g_line.size_buf);
	g_dis.cbpos = 0;
	g_line.len = 0;
	g_cursor.c_pos = 0;
	if (g_cursor.v_pos != g_dis.botl)
		ft_putstr(tgoto(g_termcaps.DO, 0, g_dis.botl - g_cursor.v_pos));
	g_cursor.v_pos = 0;
	write(STDOUT_FILENO, "\n", 1);
	update_line();
}

void rl_insert(int c)
{
	char s[1];

	s[0] = (char)c;
	insert_text(s, 1);
}

void cursor_l(void)
{
	if (g_dis.cbpos > 0)
	{
		if (g_cursor.c_pos > 0)
		{
			ft_putstr(tgoto(g_termcaps.backspace, 0, 0));
			--g_cursor.c_pos;
		}
		else
		{
			g_cursor.c_pos = g_sc.w - 1;
			--g_cursor.v_pos;
			ft_putstr(tgoto(g_termcaps.up, 0, 0));
			ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		}
		g_dis.cbpos -= 1;
		update_line();
	}
}

void cursor_r(void)
{
	if (g_dis.cbpos < g_line.len)
	{
		if (g_cursor.c_pos == g_sc.w)
		{
			g_cursor.c_pos = 0;
			++g_cursor.v_pos;
			ft_putstr(tgoto(g_termcaps.do1, 0, 0));
			ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		}
		else
		{
			++g_cursor.c_pos;
			ft_putstr(tgoto(g_termcaps.forward_char, 0, 0));
		}
		g_dis.cbpos += 1;
		update_line();
	}
}

void cursor_d(void)
{
	int len_last_line;

	if (g_cursor.v_pos != g_dis.botl)
	{
		len_last_line = (g_dis.prompt_l + g_line.len) % g_sc.w;
		if (g_cursor.v_pos == g_dis.botl - 1
				&& g_cursor.c_pos > len_last_line)
		{
			ft_putstr(tgoto(g_termcaps.ch, 0, len_last_line));
			g_dis.cbpos = g_line.len;
		}
		else
			g_dis.cbpos += g_sc.w;
		++g_cursor.v_pos;
		ft_putstr(tgoto(g_termcaps.do1, 0, 0));
		update_line();
	}
}

void cursor_u(void)
{
	if (g_cursor.v_pos != 0)
	{
		if (g_cursor.v_pos == 1 && g_cursor.c_pos < g_dis.prompt_l)
		{
			ft_putstr(tgoto(g_termcaps.ch, 0, g_dis.prompt_l));
			g_dis.cbpos = 0;
		}
		else
			g_dis.cbpos -= g_sc.w;
		--g_cursor.v_pos;
		ft_putstr(tgoto(g_termcaps.up, 0, 0));
		update_line();
	}
}

static void clear_line(void)
{
	rl_home();
	ft_putstr(g_termcaps.clreol);
	g_line.len = 0;
	ft_bzero(g_line.line, g_line.size_buf);
}

void hist_lookup(void)
{
	char buf[10000];
	char *tmp;
	char *prompt;
	union u_buffer c;
	int i;

	tmp = g_line.line;
	i = 0;
	c.value = 1;
	ft_bzero(buf, 10000);
	prompt = ft_strdup(g_dis.prompt);
	set_prompt("(reverse-i-search)");
	while (ft_isprint(buf[i]) || !buf[i])
	{
		ft_putstr(tgoto(g_termcaps.ch, 0, 0));
		ft_putstr(g_dis.prompt);
		ft_putstr(tgoto(g_termcaps.clreol, 0, 0));
		ft_printf("`%s': %s", buf, tmp);
		c = read_key();
		if (c.value == 127 && i > 0)
			i--;
		if (test_c_value(c))
			break ;
		if (i >= 0)
			buf[i] = (c.value == 127) ? '\0' : c.value;
		if (c.value != 127)
			i++;
		if (c.value != 127 && !(get_matching_hist(&tmp, buf)))
			set_prompt("(failed reverse-i-search)");
		else if (ft_strequ(g_dis.prompt, "(failed reverse-i-search)"))
			set_prompt("(reverse-i-search)");
	}
	g_hist_lookup_value = c.value;
	set_prompt(prompt);
	free(prompt);
	if (i != 0 || tmp[0])
	{
		free(g_line.line);
		if (!(g_line.line = (char *)ft_memalloc(sizeof(char) * g_line.size_buf)))
			ft_printf("./21sh: cannot allocate memory\n");
		g_line.line = ft_memcpy(g_line.line, tmp, ft_strlen(tmp));
		g_line.len = ft_strlen(tmp);
		g_dis.cbpos = g_line.len;
	}
	update_line();
	return ;
}

char *get_matching_hist(char **line, char *patern)
{
	char *tmp;


	tmp = *line;
	if (!tmp)
		return (tmp);
	while (!ft_strstr(tmp, patern) && g_hist->nb_line > 0)
		tmp = prev_hist();
	if (ft_strstr(tmp, patern))
		*line = tmp;
	else
	{
		while (!ft_strstr(tmp, *line)
	&& g_hist->nb_line < g_hist->total_lines)
			tmp = next_hist();
		*line = tmp;
		tmp = NULL;
	}
	return (tmp);
}

int test_c_value(union u_buffer c)
{
	if ((ft_isprint(c.value) && c.value != 9) || c.value == 127)
		return (0);
	if (enter_rc(c))
		return (1);
	if (isctrlkey(c))
		return (1);
	if (ismetachar(c))
		return (1);
	if (isstdkey(c.value))
		return (1);
	return (0);
}

void history_up(void)
{
	char *s;

	if (g_hist->offset == g_hist->used - 1)
	{
		if (g_original_cmd)
			free(g_original_cmd);
		if (!(g_original_cmd = ft_strdup(g_line.line)))
		{
			ft_printf("./21sh: cannot allocate mmemory\n");
			return ;
		}
	}
	s = prev_hist();
	clear_line();
	insert_text(s, ft_strlen(s));
}

void history_down(void)
{
	char *s;

	s = next_hist();
	clear_line();
	if (*s)
		insert_text(s, ft_strlen(s));
	else
		insert_text(g_original_cmd, ft_strlen(g_original_cmd));
}

void rl_home(void)
{
	g_cursor.c_pos = g_dis.prompt_l;
	if (g_cursor.c_pos > 0)
		ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
	if (g_cursor.v_pos > 0)
	{
		ft_putstr(tgoto(g_termcaps.UP, 0, g_cursor.v_pos));
		g_cursor.v_pos = 0;
	}
	g_dis.cbpos = 0;
	update_line();
}


void rl_end(void)
{
	g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
	if (g_cursor.c_pos > 0)
	{
		ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
		g_dis.cbpos = g_line.len;
	}
	if (g_cursor.v_pos != g_dis.botl)
	{
		ft_putstr(tgoto(g_termcaps.DO, 0, g_dis.botl - g_cursor.v_pos));
		g_dis.cbpos = g_line.len;
		g_cursor.v_pos = (g_dis.prompt_l + g_dis.cbpos) / g_sc.w;
	}
	update_line();
}

void wd_right(void)
{
	while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
	while (g_line.line[g_dis.cbpos] != ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
}

void wd_left(void)
{
	while (g_dis.cbpos > 0 && g_line.line[g_dis.cbpos - 1] == ' ')
		cursor_l();
	while (g_dis.cbpos > 0 && g_line.line[g_dis.cbpos - 1] != ' ')
		cursor_l();
}

void clear_scr(void)
{
	ft_putstr(g_termcaps.clrpag);
	update_line();
}


void rl_void(void)
{
	ft_putstr(g_termcaps.bl);
	return;
}

void paste_via_input(unsigned long v)
{
	union u_buffer u;
	int len;

	len = 0;
	u.value = v;
	while (len < 8 && u.buf[len])
		++len;
	insert_text(&(u.buf[0]), len);
}


void clear_eol(void)
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


void clip_paste(void)
{
	insert_text(g_clip.str, g_clip.l);
}


void clear_befline(void)
{
	if (g_dis.cbpos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(g_line.line, g_dis.cbpos);
		g_clip.l = g_dis.cbpos;
		g_line.len -= g_dis.cbpos;
		ft_memmove(g_line.line, &(g_line.line[g_dis.cbpos]),
		g_dis.cbpos);
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_dis.cbpos = 0;
		rl_home();
	}
}


void cut_prev_wd(void)
{
	int start;

	if (g_dis.cbpos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		start = g_dis.cbpos;
		while (start && g_line.line[start - 1] == ' ')
			--start;
		while (start && g_line.line[start - 1] != ' ')
			--start;
		g_clip.l = g_dis.cbpos - start;
		g_clip.str = ft_strndup(&(g_line.line[start]), g_clip.l);
		ft_memmove(&(g_line.line[start]),
		&(g_line.line[g_dis.cbpos]), g_line.len - g_dis.cbpos);
		g_line.len -= g_clip.l;
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_dis.cbpos = start;
		update_line();
	}
}
