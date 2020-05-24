/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 11:47:46 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	cmaj_motion(void)
{
	ft_bzero(g_line.line + g_line.c_pos, g_line.len - g_line.c_pos);
	vim_insert();
	g_line.len = g_line.c_pos;
	g_line.is_modified = 1;
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
		g_line.c_pos = 0;
		g_line.is_modified = 1;
	}
}

void	dmaj_motion(void)
{
	g_clip.l = g_line.len - g_line.c_pos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
	ft_bzero(&(g_line.line[g_line.c_pos]), g_clip.l);
	g_line.len -= g_clip.l;
	cursor_l();
	g_line.is_modified = 1;
}

/*
** 
**
**
*/

void	yank_c(void)
{
	union u_buffer	c;

	c = read_key();
	add_back();
	if (isctrlkey(c))
	{
		if (c.buf[2] == 67)
		{
			clear_eol();
			vim_insert();
		}
		else if (c.buf[2] == 68)
		{
			clear_eol();
			cursor_l();
		}
		else if (c.buf[2] == 65) // up
		{
			rl_end();
			vim_insert();
		}
		else if (c.buf[2] == 66) // down
			rl_home();
		return ;
	}
//	ft_printf("\n\n%d, %d, %d, %d, %d, %d\n\n", c.buf[0], c.buf[1], c.buf[2], c.buf[3], c.buf[4], c.buf[5]);
//	else if (c == 'b') // copy the word till ; before cursor but no move
//	if (c == 'B') // copy the whole word before cursor but no move
//	else if (c == 'E') // from cursor till end no cursor move
//	else if (c == 'e') // from cursor till find ; or this kind of char
//	else if (c == 'y') // copy all line no move
//	else if (c == )
//	ft_printf("\n\nOKOKOKi\n\n");
	g_clip.l = 1;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
}

void	yank_eol(void)
{
	ft_printf("\n\nOKOKOKi\n\n");
	g_clip.l = g_line.len - g_line.c_pos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
}
