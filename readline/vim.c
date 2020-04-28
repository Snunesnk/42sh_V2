/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:10 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/28 17:29:43 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (g_line.len > 0 && !ft_str_isspace(g_line.line))
		add_hentry(g_line.line, g_line.len, 1);
	add_hentry("fc", 2, 1);
	argv[0] = "fc";
	argv[1] = NULL;
	deprep_terminal();
	rl_clear_signals();
	cmd_fc(1, argv);
	rl_set_signals();
	prep_terminal();
	g_bad_seq.value = '\n';
	g_input_break = 1;
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
