/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:43 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 19:29:15 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	cmaj_motion(void)
{
	ft_bzero(&g_line.line[g_line.c_pos], g_line.len - g_line.c_pos);
	vim_insert();
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

void	yank_c(void)
{
	int	c;

	c = 0;
	if (read(STDIN_FILENO, &c, sizeof(int)) < 0)
		return ;
	if (c == 'b') // copy the word till ; before cursor but no move
	if (c == 'B') // copy the whole word before cursor but no move
	else if (c == 'E') // from cursor till end no cursor move
	else if (c == 'e') // from cursor till find ; or this kind of char
	else if (c == 'y') // copy all line no move
	else if (c == )
	ft_printf("\n\nOKOKOKi\n\n");
	g_clip.l = 1;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
}

void	yank_eol(void)
{
	g_clip.l = g_line.len - g_line.c_pos;
	if (g_clip.str != NULL)
		free(g_clip.str);
	g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
}
