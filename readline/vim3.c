/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 18:09:43 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	goto_pchr_left(void)
{
	int	p;

	if (!g_got_input)
	{
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
	g_line.c_pos = g_line.len;
	vim_insert();
}
