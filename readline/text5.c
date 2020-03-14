/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:13:39 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:39:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	clip_paste(void)
{
	insert_text(g_clip.str, g_clip.l);
}

void	clear_befline(void)
{
	if (g_dis.cbpos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(g_line.line, g_dis.cbpos);
		g_clip.l = g_dis.cbpos;
		g_line.len -= g_dis.cbpos;
		ft_memmove(g_line.line, &(g_line.line[g_dis.cbpos]),
		g_dis.cbpos);
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_dis.cbpos = 0;
		rl_home();
	}
}

void	cut_prev_wd(void)
{
	int start;

	if (g_dis.cbpos != 0)
	{
		if (g_clip.str != NULL)
			free(g_clip.str);
		start = g_dis.cbpos;
		while (start && g_line.line[start - 1] == ' ')
			--start;
		while (start && g_line.line[start - 1] != ' ')
			--start;
		g_clip.l = g_dis.cbpos - start;
		g_clip.str = ft_strndup(&(g_line.line[start]), g_clip.l);
		ft_memmove(&(g_line.line[start]),
		&(g_line.line[g_dis.cbpos]), g_line.len - g_dis.cbpos);
		g_line.len -= g_clip.l;
		ft_bzero(&(g_line.line[g_line.len]), g_clip.l);
		g_dis.cbpos = start;
		update_line();
	}
}

void    rl_reversel(void)
{
	char c;

	if (g_line.len > 1)
	{
		if (g_line.len > 1 && g_dis.cbpos == g_line.len)
		{
			c = g_line.line[g_dis.cbpos - 1];
			g_line.line[g_dis.cbpos - 1] = g_line.line[g_dis.cbpos - 2];
			g_line.line[g_dis.cbpos - 2] = c;
			update_line();
		}
		else if (g_dis.cbpos > 0)
		{
			c = g_line.line[g_dis.cbpos];
				g_line.line[g_dis.cbpos] = g_line.line[g_dis.cbpos - 1];
			g_line.line[g_dis.cbpos - 1] = c;
			cursor_r();
		}
	}
}
