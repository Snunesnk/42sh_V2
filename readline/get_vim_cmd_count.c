/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vim_cmd_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 12:52:13 by snunes            #+#    #+#             */
/*   Updated: 2020/05/24 15:09:45 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	g_vim_cmd_count = 0;

static void		print_count(void)
{
	ft_putstr_fd(tgoto(g_termcaps.cm, 0, g_dis.start_line), g_dis.fd);
	ft_dprintf(g_dis.fd, "(arg: %d) ", g_vim_cmd_count);
	get_cursor_position(&(g_dis.start_line), &(g_dis.start_offset));
	g_line.is_modified = 1;
	g_line.cursor_pos = 0;
	update_line();
}

static void		put_prompt_back(void)
{
	ft_putstr_fd(tgoto(g_termcaps.cm, 0, g_dis.start_line), g_dis.fd);
	display_prompt();
	g_line.is_modified = 1;
	g_line.cursor_pos = 0;
	update_line();
}

union u_buffer	get_vim_cmd_count(union u_buffer c)
{
	g_vim_cmd_count = 0;
	if (!g_vim_mode || !g_vim_cmd || !ft_isdigit(c.value) || c.value == '0')
		return (c);
	while (ft_isdigit(c.value))
	{
		g_vim_cmd_count = g_vim_cmd_count * 10 + c.value - '0';
		if (g_vim_cmd_count > 1000000)
		{
			put_prompt_back();
			c = read_key();
			return (get_vim_cmd_count(c));
		}
		print_count();
		c = read_key();
	}
	put_prompt_back();
	return (c);
}
