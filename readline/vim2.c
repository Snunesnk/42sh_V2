#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	end_next_alnum(void)
{
	if (g_dis.cbpos < g_line.len)
		cursor_r();
	if (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		while (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
			cursor_r();
	if (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_dis.cbpos + 1])
			&& g_dis.cbpos + 1 < g_line.len)
			cursor_r();
	}
	else if (ft_ispunct(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_ispunct(g_line.line[g_dis.cbpos + 1])
			&& g_dis.cbpos + 1 < g_line.len)
			cursor_r();
	}
}

void	end_next_wd(void)
{
	if (ft_isspace(g_line.line[g_dis.cbpos + 1]))
		cursor_r();
	while (ft_isspace(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		cursor_r();
	while (!ft_isspace(g_line.line[g_dis.cbpos + 1])
		&& g_dis.cbpos + 1 < g_line.len)
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
	int			p;
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
	int			p;
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
		while (p >= 0)
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
