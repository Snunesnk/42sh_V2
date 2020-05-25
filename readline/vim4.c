/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:37 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 16:14:51 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	insert_mode_first(void)
{
	g_line.c_pos = 0;
	vim_insert();
	g_line.is_modified = 1;
}

void	replace_wd(void)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	if (read(STDIN_FILENO, &c, sizeof(int)) < 0)
		return ;
	if (ft_isprint(c))
	{
		while (g_line.c_pos + i <= g_line.len \
				&& (i < g_vim_cmd_count || i == 0))
		{
			g_line.line[g_line.c_pos + i] = c;
			g_line.is_modified = 1;
			i++;
		}
		g_line.c_pos += i - 1;
	}
}

void	replace_mode(void)
{
	vim_insert();
	g_replace_mode = 1;
}

void	clear_all_l(void)
{
	ft_bzero(g_line.line, g_line.len);
	g_line.c_pos = 0;
	vim_insert();
	g_line.is_modified = 1;
	g_line.len = 0;
}

void	c_motion(void)
{
	union u_buffer	c;
	static char		poss[] = " 0biFlW^$;EfTw|,BehtC";
	int				ret;

	ret = g_line.c_pos;
	c.value = 0;
	if (read(STDIN_FILENO, c.buf, sizeof(int)) < 0)
		return ;
	if (!ft_strchr(poss, c.value))
		return ;
	if (c.value == 'C')
		g_line.c_pos = 0;
	(g_standard_keymap[c.value].func)(c.value);
	if (c.value == 'C')
		return ;
	add_back();
	if (ret < g_line.c_pos)
		del_from_to(ret, g_line.c_pos + 1, NO_SAVE);
	else
		del_from_to(g_line.c_pos, ret, NO_SAVE);
	vim_insert();
}
