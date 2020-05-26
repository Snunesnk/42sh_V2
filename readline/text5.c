/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:13:39 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/26 10:18:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	clip_paste(void)
{
	insert_text(g_clip.str, g_clip.l, 1);
}

void	clear_befline(void)
{
	if (g_line.c_pos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(g_line.line, g_line.c_pos);
		g_clip.l = g_line.c_pos;
		g_line.len -= g_line.c_pos;
		add_back();
		ft_memmove(g_line.line, g_line.line + g_line.c_pos, g_line.len);
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_line.c_pos = 0;
		rl_home();
		g_line.is_modified = 1;
	}
}

void	cut_prev_wd(void)
{
	int start;

	if (g_line.c_pos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		add_back();
		start = g_line.c_pos;
		while (start && g_line.line[start - 1] == ' ')
			--start;
		while (start && g_line.line[start - 1] != ' ')
			--start;
		g_clip.l = g_line.c_pos - start;
		g_clip.str = ft_strndup(&(g_line.line[start]), g_clip.l);
		ft_memmove(&(g_line.line[start]),
		&(g_line.line[g_line.c_pos]), g_line.len - g_line.c_pos);
		g_line.len -= g_clip.l;
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_line.c_pos = start;
		g_line.is_modified = 1;
	}
}

void	rl_reversel(void)
{
	char	c;

	if (g_line.len > 1)
	{
		add_back();
		if (g_line.len > 1 && g_line.c_pos == g_line.len)
		{
			c = g_line.line[g_line.c_pos - 1];
			g_line.line[g_line.c_pos - 1] = g_line.line[g_line.c_pos - 2];
			g_line.line[g_line.c_pos - 2] = c;
		}
		else if (g_line.c_pos > 0)
		{
			c = g_line.line[g_line.c_pos];
			g_line.line[g_line.c_pos] = g_line.line[g_line.c_pos - 1];
			g_line.line[g_line.c_pos - 1] = c;
			cursor_r();
			g_line.is_modified = 1;
		}
		g_line.cursor_pos = 0;
	}
}

void	cut_next_wd(void)
{
	int	start;

	if (g_clip.str != NULL)
		free(g_clip.str);
	add_back();
	start = g_line.c_pos;
	while (start < g_line.len && g_line.line[start] == ' ')
		++start;
	while (start < g_line.len && g_line.line[start] != ' ')
		++start;
	g_clip.l = start - g_line.c_pos;
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
	ft_memmove(&(g_line.line[g_line.c_pos]),
	&(g_line.line[start]), g_line.len - start);
	g_line.len -= g_clip.l;
	ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
	g_line.is_modified = 1;
}
