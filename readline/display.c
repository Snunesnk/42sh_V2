/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 21:14:06 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

struct s_display	g_dis =
{
	.prompt = NULL,
	.display_prompt = NULL,
	.prompt_l = 0,
	.real_prompt_l = 0,
	.start_offset = 0,
};

struct s_line_state	g_line =
{
	.line = NULL,
	.size_buf = 0,
	.c_pos = 0,
	.cursor_pos = 0,
	.len = 0,
	.is_modified = 0
};

void		display_prompt(void)
{
	if (write(STDERR_FILENO, g_dis.display_prompt, g_dis.real_prompt_l) < 0)
		return ;
}

void		set_prompt(const char *prompt)
{
	if (g_dis.prompt != NULL)
		free(g_dis.prompt);
	if (prompt)
		g_dis.prompt = ft_strdup(prompt);
	else
		g_dis.prompt = NULL;
	if (g_dis.prompt == NULL)
		g_dis.display_prompt = "";
	else
		g_dis.display_prompt = g_dis.prompt;
	g_dis.prompt_l = get_vis_prompt_len(g_dis.display_prompt);
	g_dis.real_prompt_l = ft_strlen(g_dis.display_prompt);
}

void		clear_next()
{
	int	v_pos;
	int	c_pos;

	v_pos = 0;
	c_pos = 0;
	ft_putstr(g_termcaps.clreol);
	calc_dcursor(g_line.len, &v_pos, &c_pos);
	if (v_pos >= g_sc.height - 1)
		return ;
	ft_putstr(tgoto(g_termcaps.cm, 0, v_pos + 1));
	ft_putstr(g_termcaps.cd);
	ft_putstr(tgoto(g_termcaps.cm, c_pos, v_pos));
}

void		update_line(void)
{
	int	ret;

	if (g_dumb_term)
		return (update_dumb_line());
	if (g_line.is_modified)
	{
		ret = g_line.cursor_pos;
		place_cursor(g_line.len);
		place_cursor(ret);
		ft_putstr(G_LINE_COLOR);
		if (g_line.c_pos < g_line.cursor_pos)
		{
			place_cursor(g_line.c_pos);
			write(STDOUT_FILENO, g_line.line + g_line.c_pos, \
					g_line.len - g_line.c_pos);
		}
		else
			write(STDOUT_FILENO, g_line.line + g_line.cursor_pos, \
					g_line.len - g_line.cursor_pos);
		g_line.cursor_pos = g_line.len;
		ft_putstr(END_OF_COLOR);
		clear_next();
	}
	place_cursor(g_line.c_pos);
	g_line.is_modified = 0;
}

int		calc_v_pos(void)
{
	int	v_pos;
	int	c_pos;
	int	track;

	track = 0;
	v_pos = g_dis.start_offset / g_sc.w;
	c_pos = g_dis.start_offset % g_sc.w;
	while (track != g_line.c_pos)
	{
		if (c_pos == g_sc.w || g_line.line[track] == '\n')
		{
			c_pos = 0;
			v_pos++;
		}
		track++;
	}
	return (v_pos);
}

void		redisplay_after_sigwinch(void)
{
	struct winsize	w_size;
	int				ret;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w_size) == -1)
		return ;
	g_sc.w = w_size.ws_col;
	g_sc.height = w_size.ws_row;
	if (g_dumb_term)
	{
		ft_printf("\r%.*s\r", g_sc.w, "");
		return ;
	}
	if (g_dis.start_line > g_sc.height- 1)
		g_dis.start_line = g_sc.height - 1;
	ret = g_dis.start_line;
	ft_putstr(tgoto(g_termcaps.cm, 0, g_dis.start_line));
	ft_putstr(g_termcaps.cd);
	display_prompt();
	get_cursor_position(&(g_dis.start_line), &(g_dis.start_offset));
	g_dis.start_line = ret;
	g_line.cursor_pos = 0;
	g_line.is_modified = 1;
	update_line();
}
