/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 13:23:37 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	cmaj_motion(void)
{
	del_from_to(g_line.c_pos, g_line.len, NO_SAVE);
	vim_insert();
}

void	d_motion(void)
{
	union u_buffer	c;
	static char		poss[] = " 0biFlW^$;EfTw|,Behtd";
	int				ret;

	ret = g_line.c_pos;
	c.value = 0;
	if (read(STDIN_FILENO, c.buf, sizeof(int)) < 0)
		return ;
	if (!ft_strchr(poss, c.value))
		return ;
	if (c.value != 'd')
		(g_standard_keymap[c.value].func)(c.value);
	else
	{
		del_from_to(0, g_line.len, SAVE);
		return ;
	}
	if (ret < g_line.c_pos)
		del_from_to(ret, g_line.c_pos + 1, SAVE);
	else
		del_from_to(ret, g_line.c_pos + 1, NO_SAVE);
}


void	dmaj_motion(void)
{
	del_from_to(g_line.c_pos, g_line.len, SAVE);
	cursor_l();
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
