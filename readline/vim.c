/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:10 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 18:55:17 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	replace_text(const char *string, int len)
{
	int nlen;

	nlen = g_line.c_pos + len;
	while (nlen >= g_line.size_buf)
		l_expand();
	ft_strncpy(&g_line.line[g_line.c_pos], string, len);
	if (nlen > g_line.len)
		g_line.len = nlen;
	g_line.c_pos += len;
	g_line.is_modified = 1;
}

void	vim_hash(void)
{
	g_input_break = 1;
	g_line.c_pos = 0;
	insert_text("#", 1);
}

void	call_fc(void)
{
	char *argv[2];

	if (g_line.len > 0 && !ft_str_isspace(g_line.line))
		add_hentry(g_line.line, g_line.len);
	add_hentry("fc", 2);
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
	while (g_line.line[g_line.c_pos] != ' ' && g_line.c_pos < g_line.len)
		cursor_r();
	while (g_line.line[g_line.c_pos] == ' ' && g_line.c_pos < g_line.len)
		cursor_r();
}

void	beg_next_alnum(void)
{
	if (ft_isalnum(g_line.line[g_line.c_pos]) && g_line.c_pos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_line.c_pos]) && g_line.c_pos < \
				g_line.len)
			cursor_r();
		while (g_line.line[g_line.c_pos] == ' ' && g_line.c_pos < g_line.len)
			cursor_r();
	}
	else if (!ft_isalnum(g_line.line[g_line.c_pos]) && g_line.c_pos < \
			g_line.len)
		while (!ft_isalnum(g_line.line[g_line.c_pos])
			&& g_line.c_pos < g_line.len)
			cursor_r();
}
