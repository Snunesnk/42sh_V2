/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 20:13:21 by snunes           ###   ########.fr       */
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
	.prev_c_pos = 0,
	.is_modified = 0,
	.len = 0
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

static char	*print_pos_line(int shift)
{
	char	*pos_line;
	int		len;

	len = sizeof(char);
	if (shift > 0)
		len *= shift * ft_strlen(tgoto(g_termcaps.backspace, 0, 0));
	else
		len *= -shift * ft_strlen(tgoto(g_termcaps.forward_char, 0, 0));
	if (!(pos_line = ft_memalloc(len)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	while (shift < 0)
	{
		ft_strcat(pos_line, g_termcaps.backspace);
		shift++;
	}
	while (shift > 0)
	{
		ft_strcat(pos_line, g_termcaps.forward_char);
		shift--;
	}
	return (pos_line);
}

void		place_cursor(int pos)
{
	char	*pos_line;
	int		start_pos;
	int		shift;

	shift = 0;
	start_pos = g_line.c_pos;
	if (start_pos == pos)
		return ;
	while (start_pos != pos)
	{
		if (start_pos > pos)
			shift--;
		else
			shift++;
		start_pos = (start_pos > pos) ? start_pos - 1 : start_pos + 1;
	}
	if (!(pos_line = print_pos_line(shift)))
		exit (e_cannot_allocate_memory);
	shift = write(STDOUT_FILENO, pos_line, ft_strlen(pos_line));
	g_line.c_pos = pos;
	free(pos_line);
}

void		update_line(void)
{
	int	ret;

	ret = g_line.c_pos;
	if (g_line.is_modified)
	{
		ft_putstr(G_LINE_COLOR);
		if (g_line.c_pos < g_line.prev_c_pos)
			write(STDOUT_FILENO, g_line.line + g_line.c_pos, \
					g_line.len - g_line.c_pos);
		else
		{
			place_cursor(g_line.prev_c_pos);
			write(STDOUT_FILENO, g_line.line + g_line.prev_c_pos, \
					g_line.len - g_line.prev_c_pos);
		}
		g_line.c_pos = g_line.len;
		ft_putstr(END_OF_COLOR);
	}
	place_cursor(ret);
	g_line.prev_c_pos = g_line.c_pos;
	g_line.is_modified = 0;
	return ;
}

void		redisplay_after_sigwinch(void)
{
	return ;
}/*
	g_dis.fst_line_l = g_sc.w - (g_dis.prompt_l % g_sc.w);
	g_cursor.c_pos = (g_dis.prompt_l + g_dis.cbpos) % g_sc.w;
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
	ft_putstr(END_OF_COLOR);
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
}*/
