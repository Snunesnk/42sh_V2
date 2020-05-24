/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 17:34:10 by snunes            #+#    #+#             */
/*   Updated: 2020/05/24 15:55:25 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

void	goto_n_char(void)
{
	g_line.c_pos = g_vim_cmd_count;
	if (g_line.c_pos > g_line.len)
		g_line.c_pos = g_line.len;
}

void	vim_delete(void)
{
	int	len;

	add_back();
	if (g_line.len == 0)
		return ;
	if (!g_vim_cmd_count)
		g_vim_cmd_count = 1;
	if ((len = g_line.c_pos + g_vim_cmd_count) > g_line.len)
		len = g_line.len;
	len -= g_line.c_pos;
	if (g_clip.str)
		free(g_clip.str);
	if (!(g_clip.str = ft_strndup(g_line.line + g_line.c_pos, len)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	g_clip.l = len;
	while (len--)
		rl_delete();
	if (g_line.c_pos == g_line.len)
		cursor_l();
}

void	vim_backspace(void)
{
	int	len;

	add_back();
	if (g_line.len == 0 || g_line.c_pos == 0)
		return ;
	if (!g_vim_cmd_count)
		g_vim_cmd_count = 1;
	if ((len = g_line.c_pos - g_vim_cmd_count) < 0)
		len = 0;
	if (g_clip.str)
		free(g_clip.str);
	if (!(g_clip.str = ft_strndup(g_line.line + len, g_line.c_pos - len)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	g_clip.l = g_line.c_pos - len;
	while (g_line.c_pos > len)
		rl_backspace();
}

void	del_from_to(int start, int end, int save_mode)
{
	int	len;

	len = end - start;
	if (save_mode == SAVE)
	{
		if (g_clip.str)
			free(g_clip.str);
		if (!(g_clip.str = ft_strndup(g_line.line + start, len)))
		{
			psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
			return ;
		}
		g_clip.l = len;
	}
	ft_memmove(g_line.line + start, g_line.line + end, g_line.size_buf - end);
	g_line.is_modified = 1;
	g_line.len -= len;
	g_line.c_pos = start;
}
