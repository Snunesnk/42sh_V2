/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:03:00 by snunes            #+#    #+#             */
/*   Updated: 2020/05/07 15:09:44 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

/*
** These two functions scroll the screen, to access a line that is after or \
** before the displayed lines
*/
static void	scroll_up(void)
{
	ft_putstr(tgoto(g_termcaps.cm, g_sc.w - 1, g_sc.height - 1));
	ft_putstr(g_termcaps.sf);
	g_dis.start_line -= 1;
}

static void	scroll_down(void)
{
	ft_putstr(tgoto(g_termcaps.cm, 0, 0));
	ft_putstr(g_termcaps.sr);
	g_dis.start_line += 1;
}

/*
** Determine the coordinates of the wanted position
*/
void		calc_dcursor(int pos, int *v_pos, int *c_pos)
{
	int	track;

	*v_pos = g_dis.start_line;
	*c_pos = g_dis.start_offset;
	track = 0;
	while (track < pos)
	{
		if (*c_pos == g_sc.w - 1 || g_line.line[track] == '\n')
		{
			*c_pos = 0;
			*v_pos += 1;
		}
		else
			(*c_pos)++;
		track++;
	}
}

/*
** calculate the coordinates of the wanted position, then perform scroll if \
** needed, then use cm to place the cursor at the wanted position
*/
void		place_cursor(int pos)
{
	int	v_pos;
	int	c_pos;

	v_pos = 0;
	c_pos = 0;
	calc_dcursor(pos, &v_pos, &c_pos);
	while (v_pos > g_sc.height - 1)
	{
		scroll_up();
		v_pos -= 1;
	}
	while (v_pos < 0)
	{
		scroll_down();
		v_pos += 1;
	}
	ft_putstr(tgoto(g_termcaps.cm, c_pos, v_pos));
	g_line.cursor_pos = pos;
}

