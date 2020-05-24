/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:23 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 21:46:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

char	g_last_goto = 0;

void	end_next_alnum(void)
{
	if (g_line.c_pos < g_line.len)
		cursor_r();
	if (ft_isspace(g_line.line[g_line.c_pos]) && g_line.c_pos < g_line.len)
		while (ft_isspace(g_line.line[g_line.c_pos]) && g_line.c_pos < \
				g_line.len)
			cursor_r();
	if (ft_isalnum(g_line.line[g_line.c_pos]) && g_line.c_pos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_line.c_pos + 1])
			&& g_line.c_pos + 1 < g_line.len)
			cursor_r();
	}
	else if (ft_ispunct(g_line.line[g_line.c_pos]) && g_line.c_pos < g_line.len)
	{
		while (ft_ispunct(g_line.line[g_line.c_pos + 1])
			&& g_line.c_pos + 1 < g_line.len)
			cursor_r();
	}
	if (--g_vim_cmd_count > 0 && g_line.c_pos < g_line.len)
		end_next_alnum();
}

void	end_next_wd(void)
{
	if (ft_isspace(g_line.line[g_line.c_pos + 1]))
		cursor_r();
	while (ft_isspace(g_line.line[g_line.c_pos]) && g_line.c_pos < g_line.len)
		cursor_r();
	while (!ft_isspace(g_line.line[g_line.c_pos + 1])
		&& g_line.c_pos + 1 < g_line.len)
		cursor_r();
	if (--g_vim_cmd_count > 0 && g_line.c_pos < g_line.len)
		end_next_wd();
}

void	beg_last_alnum(void)
{
	if (g_line.c_pos > 0)
		cursor_l();
	if (g_line.c_pos > 0 && ft_isspace(g_line.line[g_line.c_pos]))
		while (g_line.c_pos > 0 && ft_isspace(g_line.line[g_line.c_pos]))
			cursor_l();
	if (g_line.c_pos > 0 && ft_isalnum(g_line.line[g_line.c_pos]))
	{
		while (g_line.c_pos > 0 && ft_isalnum(g_line.line[g_line.c_pos - 1]))
			cursor_l();
	}
	else if (g_line.c_pos > 0 && ft_ispunct(g_line.line[g_line.c_pos]))
	{
		while (g_line.c_pos > 0 && ft_ispunct(g_line.line[g_line.c_pos - 1]))
			cursor_l();
	}
	if (--g_vim_cmd_count > 0 && g_line.c_pos > 0)
		beg_last_alnum();
}

void	goto_chr_right(void)
{
	int			p;

	if (!g_got_input)
	{
		g_last_goto = 'f';
		if (read(STDIN_FILENO, &g_c, sizeof(int)) < 0)
			return ;
	}
	p = g_line.c_pos + 1;
	if (ft_isprint(g_c))
	{
		while (p < g_line.len)
		{
			if (g_line.line[p] == g_c)
				g_line.c_pos = p;
			if (g_line.line[p] == g_c && --g_vim_cmd_count <= 0)
				return ;
			++p;
		}
	}
}

void	goto_chr_left(void)
{
	int			p;

	if (!g_got_input)
	{
		g_last_goto = 'F';
		if (read(STDIN_FILENO, &g_c, sizeof(int)) < 0)
			return ;
	}
	p = g_line.c_pos - 1;
	if (ft_isprint(g_c))
	{
		while (p >= 0)
		{
			if (g_line.line[p] == g_c)
				g_line.c_pos = p;
			if (g_line.line[p] == g_c && --g_vim_cmd_count <= 0)
				return ;
			--p;
		}
	}
}
