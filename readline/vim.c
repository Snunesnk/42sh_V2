#include "ft_readline.h"
#include "../src/builtins/builtins.h"

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
	int	p;
	char	c;

	c = 0;
	p = g_dis.cbpos;
	read(STDIN_FILENO, &c, 1);
	if (ft_isalnum(c))
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
	int	p;
	char	c;

	c = 0;
	p = g_dis.cbpos;
	read(STDIN_FILENO, &c, 1);
	if (ft_isalnum(c))
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
