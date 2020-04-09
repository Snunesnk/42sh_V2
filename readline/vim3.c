/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:35:33 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	goto_pchr_left(void)
{
	int			p;
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
		while (p - 1 >= 0)
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
	int			p;
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
