/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:16:27 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:35:45 by abarthel         ###   ########.fr       */
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
	g_dis.cbpos = 0;
	g_line.len = 0;
}

static void	l_expand(void)
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
	while (len + g_line.len >= g_line.size_buf)
		l_expand();
	if (g_dis.cbpos < g_line.len)
	{
		ft_memmove(&(g_line.line[g_dis.cbpos + len]),
				&(g_line.line[g_dis.cbpos]),
				g_line.len - g_dis.cbpos);
	}
	ft_memmove(&(g_line.line[g_dis.cbpos]), string, len);
	g_line.len += len;
	g_dis.cbpos += len;
	update_line();
}

void		rl_delete(void)
{
	if (g_dis.cbpos < g_line.len && g_line.len > 0)
	{
		if (g_line.line[g_dis.cbpos] && g_dis.cbpos <= g_line.len)
		{
			ft_memmove(&(g_line.line[g_dis.cbpos]),
				&(g_line.line[g_dis.cbpos + 1]), g_line.len - g_dis.cbpos + 1);
			g_line.line[g_line.len + 1] = '\0';
			update_line();
			--g_line.len;
		}
		else if (g_dis.cbpos > 0)
		{
			g_line.line[g_dis.cbpos] = '\0';
			update_line();
			--g_line.len;
		}
	}
}

void		rl_backspace(void)
{
	if (g_dis.cbpos > 0)
	{
		cursor_l();
		if (g_line.line[g_dis.cbpos])
		{
			ft_memmove(&(g_line.line[g_dis.cbpos]),
				&(g_line.line[g_dis.cbpos + 1]), g_line.len - g_dis.cbpos + 1);
			g_line.line[g_line.len + 1] = '\0';
		}
		else
			g_line.line[g_dis.cbpos] = '\0';
		--g_line.len;
		update_line();
	}
}
