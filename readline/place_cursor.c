/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:03:00 by snunes            #+#    #+#             */
/*   Updated: 2020/05/12 19:37:40 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

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
	while (g_line.c_pos - *offset + g_dis.prompt_l >= g_sc.w - 1 \
			&& g_line.len - *offset + g_dis.prompt_l != g_sc.w)
		*offset += g_sc.w / 3;
	while (g_line.c_pos - *offset + g_dis.prompt_l <= 0 \
			|| (g_line.len + g_dis.prompt_l < g_sc.w && *offset > 0))
		*offset -= g_sc.w / 3;
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
	char		*to_print;
	static int	offset = 0;
	static int	prev_w = 0;

	if (prev_w != g_sc.w)
	{
		prev_w = g_sc.w;
		offset = 0;
	}
	ft_printf("\r%*s\r", g_sc.w, "");
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
	ft_putstr_fd(tgoto(g_termcaps.cm, c_pos, v_pos), STDOUT_FILENO);
	g_line.cursor_pos = pos;
}
