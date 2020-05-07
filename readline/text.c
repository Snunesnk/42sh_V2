/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:16:27 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 14:12:00 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_clipboard	g_clip = { .str = NULL, .l = 0 };
char				*g_original_cmd;
int					g_full_completion = 1;

void		init_line_buffer(void)
{
	g_line.size_buf = 512;
	g_line.line = (char*)malloc(sizeof(char) * g_line.size_buf);
	ft_bzero(g_line.line, g_line.size_buf);
	g_line.c_pos = 0;
	g_line.cursor_pos = 0;
	g_line.len = 0;
	g_line.is_modified = 0;
}

void		l_expand(void)
{
	char	*new;
	size_t	lold;

	lold = g_line.size_buf;
	g_line.size_buf = lold * 2;
	new = (char*)malloc(sizeof(char) * g_line.size_buf);
	ft_bzero(new, lold * 2);
	ft_strncpy(new, g_line.line, lold);
	free(g_line.line);
	g_line.line = new;
}

void		insert_text(const char *string, int len)
{
	if (g_vim_mode == 0)
	{
		g_add_back_buf += len;
		if (g_add_back_buf > 20)
		{
			g_add_back_buf = 0;
			add_back();
		}
	}
	if (g_replace_mode)
		return (replace_text(string, len));
	while (len + g_line.len >= g_line.size_buf)
		l_expand();
	if (g_line.c_pos < g_line.len)
	{
		ft_memmove(&(g_line.line[g_line.c_pos + len]),
				&(g_line.line[g_line.c_pos]),
				g_line.len - g_line.c_pos);
	}
	ft_memmove(&(g_line.line[g_line.c_pos]), string, len);
	g_line.len += len;
	g_line.c_pos += len;
	g_line.is_modified = 1;
}

void		rl_delete(void)
{
	if (g_line.c_pos < g_line.len && g_line.len > 0)
	{
		if (g_line.line[g_line.c_pos] && g_line.c_pos <= g_line.len)
		{
			ft_memmove(&(g_line.line[g_line.c_pos]),
				&(g_line.line[g_line.c_pos + 1]), g_line.len - \
				g_line.c_pos + 1);
			g_line.line[g_line.len + 1] = '\0';
			--g_line.len;
		}
		else if (g_line.c_pos > 0)
		{
			g_line.line[g_line.c_pos] = '\0';
			--g_line.len;
		}
		g_line.is_modified = 1;
	}
}

void		rl_backspace(void)
{
	if (g_line.c_pos > 0)
	{
		cursor_l();
		if (g_line.line[g_line.c_pos])
		{
			ft_memmove(&(g_line.line[g_line.c_pos]),
				&(g_line.line[g_line.c_pos + 1]), g_line.len - g_line.c_pos + 1);
			g_line.line[g_line.len + 1] = '\0';
		}
		else
			g_line.line[g_line.c_pos] = '\0';
		--g_line.len;
		g_line.is_modified = 1;
	}
}
