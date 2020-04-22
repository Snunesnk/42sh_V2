/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/22 18:16:27 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_display	g_dis =
{
	.prompt = NULL,
	.display_prompt = NULL,
	.prompt_l = 0,
	.real_prompt_l = 0,
	.botl = 0,
	.cbpos = 0,
	.line_size = 1024,
	.fst_line_l = 0
};

struct s_cursor		g_cursor =
{ .c_pos = 0, .v_pos = 0 };

struct s_line_state	g_line =
{ .line = NULL, .size_buf = 0, .len = 0 };

void		display_prompt(void)
{
	write(STDERR_FILENO, g_dis.display_prompt, g_dis.real_prompt_l);
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
	g_dis.fst_line_l = g_sc.w - g_dis.prompt_l;
}

void		display_lines(void)
{
	int	chr_l;
	int	index;

	chr_l = g_line.len;
	index = 0;
	display_prompt();
	g_dis.fst_line_l = g_sc.w - g_dis.prompt_l;
	write(STDOUT_FILENO, g_line.line, g_dis.fst_line_l);
	chr_l -= g_dis.fst_line_l;
	index += g_dis.fst_line_l;
	while (chr_l > 0)
	{
		if (g_sc.w <= chr_l)
		{
			write(STDOUT_FILENO, &(g_line.line[index]), g_sc.w);
			chr_l -= g_sc.w;
			index += g_sc.w;
		}
		else if (chr_l > 0)
		{
			write(STDOUT_FILENO, &(g_line.line[index]), chr_l);
			chr_l = 0;
		}
	}
}

void		update_line(void)
{
	ft_putstr(tgoto(g_termcaps.ch, 0, 0));
//	ft_printf("vpos: %d, prompt_l: %d, cbpos: %d\n", g_cursor.v_pos, g_dis.prompt_l, g_dis.cbpos);
	if (g_cursor.v_pos > 0)
		ft_putstr(tgoto(g_termcaps.gup, 0, g_cursor.v_pos));
	if (g_autocompl_on)
		ft_putstr(g_termcaps.clreol);
	else
		ft_putstr(g_termcaps.cd);
	g_dis.botl = (g_dis.prompt_l + g_line.len) / g_sc.w;
	g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
	g_cursor.v_pos = (g_dis.prompt_l + g_dis.cbpos) / g_sc.w;
	display_lines();
	if ((g_dis.prompt_l + g_line.len) % g_sc.w == 0)
		ft_putstr(tgoto(g_termcaps.do1, 0, 0));
	ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
	if (g_dis.botl - g_cursor.v_pos)
		ft_putstr(tgoto(g_termcaps.gup, 0, g_dis.botl - g_cursor.v_pos));
}

void		redisplay_after_sigwinch(void)
{
	g_dis.fst_line_l = g_sc.w - g_dis.prompt_l;
	g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
	if (!g_cursor.c_pos)
		g_cursor.c_pos = g_sc.w;
	g_cursor.v_pos = (g_dis.prompt_l + g_dis.cbpos) / g_sc.w;
	g_dis.botl = (g_dis.prompt_l + g_line.len) / g_sc.w;
	ft_putstr(tgoto(g_termcaps.ch, 0, 0));
	if ((g_dis.prompt_l + g_line.len) % g_sc.w == 0)
		--g_cursor.v_pos;
	if (g_cursor.v_pos > 0)
		ft_putstr(tgoto(g_termcaps.gup, 0, g_cursor.v_pos));
	ft_putstr(g_termcaps.cd);
	if (g_cursor.v_pos < 0)
		g_cursor.v_pos = 0;
	display_lines();
	if ((g_dis.prompt_l + g_line.len) % g_sc.w == 0)
		ft_putstr(tgoto(g_termcaps.do1, 0, 0));
	ft_putstr(tgoto(g_termcaps.ch, 0, g_cursor.c_pos));
	if (g_dis.botl - g_cursor.v_pos)
		ft_putstr(tgoto(g_termcaps.gup, 0, g_dis.botl - g_cursor.v_pos));
	if (g_cursor.c_pos == g_sc.w)
	{
		g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
		g_cursor.v_pos = (g_dis.prompt_l + g_dis.cbpos) / g_sc.w;
	}
}
