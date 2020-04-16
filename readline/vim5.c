/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 23:36:33 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	cmaj_motion(void)
{
	ft_bzero(&g_line.line[g_dis.cbpos], g_line.len - g_dis.cbpos);
	update_line();
	vim_insert();
}

void	d_motion(union u_buffer d)
{
	union u_buffer	c;

	c.value = 0;
	c = read_key();
	if (c.value == d.value)
	{
		g_clip.l = g_line.len;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strdup(g_line.line);
		ft_bzero(g_line.line, g_line.len);
		g_line.len = 0;
		g_dis.cbpos = 0;
		update_line();
	}
}

void	dmaj_motion(void)
{
	g_clip.l = g_line.len - g_dis.cbpos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
	ft_bzero(&(g_line.line[g_dis.cbpos]), g_clip.l);
	g_line.len -= g_clip.l;
	cursor_l();
	update_line();
}

void	yank_c(void)
{
	g_clip.l = 1;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
}

void	yank_eol(void)
{
	g_clip.l = g_line.len - g_dis.cbpos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_dis.cbpos]), g_clip.l);
}
