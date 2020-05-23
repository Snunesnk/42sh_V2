/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 21:29:49 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	goto_pchr_left(void)
{
	int	p;

	if (!g_got_input)
	{
		g_last_goto = 'T';
		g_c = 0;
		if (read(STDIN_FILENO, &g_c, sizeof(int)) < 0)
			return ;
	}
	p = g_line.c_pos - 1;
	if (ft_isprint(g_c))
	{
		while (p - 1 >= 0)
		{
			if (g_line.line[p - 1] == g_c)
				g_line.c_pos = p;
			if (g_line.line[p - 1] == g_c && --g_vim_cmd_count <= 0)
				return ;
			--p;
		}
	}
}

void	goto_pchr_right(void)
{
	int	p;

	if (!g_got_input)
	{
		g_last_goto = 't';
		g_c = 0;
		if (read(STDIN_FILENO, &g_c, sizeof(int)) < 0)
			return ;
	}
	p = g_line.c_pos + 1;
	if (ft_isprint(g_c))
	{
		while (p + 1 < g_line.len)
		{
			if (g_line.line[p + 1] == g_c)
				g_line.c_pos = p;
			if (g_line.line[p + 1] == g_c && --g_vim_cmd_count <= 0)
				return ;
			++p;
		}
	}
}

void	last_goto(void)
{
	static t_goto_func	goto_function[] = {
		{ 'f', goto_chr_right },
		{ 'F', goto_chr_left },
		{ 't', goto_pchr_right },
		{ 'T', goto_pchr_left }};
	int					i;

	i = 0;
	while (i < 4 && goto_function[i].letter != g_last_goto)
		i++;
	if (i == 4)
	{
		vim_insert();
		return ;
	}
	while (1)
	{
		g_got_input = 1;
		(*goto_function[i].func)();
		if (--g_vim_cmd_count <= 0)
			break ;
	}
	g_got_input = 0;
}

void	insert_mode_next(void)
{
	cursor_r();
	vim_insert();
}

void	insert_mode_last(void)
{
	g_line.c_pos = g_line.len;
	vim_insert();
}
