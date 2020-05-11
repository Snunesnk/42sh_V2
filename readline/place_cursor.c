/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:03:00 by snunes            #+#    #+#             */
/*   Updated: 2020/05/11 17:33:11 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

/*
** This function scroll the screen, to access a line that is after or \
** before the displayed lines
*/

static void	ft_scroll(char *direction)
{
	if (ft_strequ("down", direction))
	{
		ft_putstr(tgoto(g_termcaps.cm, 0, 0));
		ft_putstr(g_termcaps.sr);
		g_dis.start_line += 1;
	}
	else
	{
		ft_putstr_fd(tgoto(g_termcaps.cm, g_sc.w - 1, g_sc.height - 1), \
				STDERR_FILENO);
		ft_putstr_fd(g_termcaps.sf, STDERR_FILENO);
		g_dis.start_line -= 1;
	}
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
** I need to calculate the part of the string I'm going to display
*/

static char	*calc_print_range(int *offset)
{
	char	*to_print;
	int		prompt_l;

	if (!(to_print = (char *)ft_memalloc(sizeof(char) * (g_sc.w + 2))))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	while (*offset < g_sc.w)
		to_print[(*offset)++] = ' ';
	ft_dprintf(STDOUT_FILENO, "\r%s\r", to_print);
	*offset = 0;
	to_print[0] = 0;
	while (g_line.c_pos - *offset + g_dis.prompt_l >= g_sc.w - 1)
		*offset += g_sc.w / 3;
	if (*offset < g_dis.prompt_l)
		to_print = ft_strncat(to_print, g_dis.display_prompt + *offset, g_sc.w);
	if (*offset < g_dis.prompt_l)
		prompt_l = *offset;
	else
		prompt_l = g_dis.prompt_l;
	to_print = ft_strncat(to_print, g_line.line + *offset - prompt_l, g_sc.w \
			- ft_strlen(to_print));
	return (to_print);
}

void		update_dumb_line(void)
{
	char	*to_print;
	int		offset;

	offset = 0;
	if (!(to_print = calc_print_range(&offset)))
		return ;
	if (offset)
		to_print[0] = '<';
	if (ft_strlen(to_print) < (size_t)(g_line.len - offset + g_dis.prompt_l))
		to_print[g_sc.w - 1] = '>';
	ft_putstr_fd(to_print, STDOUT_FILENO);
	ft_putchar_fd('\r', STDOUT_FILENO);
	write(STDOUT_FILENO, to_print, g_line.c_pos + g_dis.prompt_l - offset);
	free(to_print);
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
		ft_scroll("up");
		v_pos -= 1;
	}
	while (v_pos < 0)
	{
		ft_scroll("down");
		v_pos += 1;
	}
	ft_putstr(tgoto(g_termcaps.cm, c_pos, v_pos));
	g_line.cursor_pos = pos;
}
