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
{
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
	else if (!ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		while (!ft_isalnum(g_line.line[g_dis.cbpos])
			&& g_dis.cbpos < g_line.len)
			cursor_r();
}
