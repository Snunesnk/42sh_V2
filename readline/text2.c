/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:14:17 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 19:04:32 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"

void	kill_line(void)
{
	write(STDOUT_FILENO, "^C", STDERR_FILENO);
	g_retval = SIGINT + 128;
	if (!g_dumb_term)
		place_cursor(g_line.len);
	ft_bzero(g_line.line, g_line.size_buf);
	g_line.len = 0;
	g_line.c_pos = 0;
	g_line.is_modified = 1;
	if (g_subprompt)
		g_input_break = 1;
	else
		write(STDOUT_FILENO, "\n", 1);
	if (!g_dumb_term)
		display_prompt();
	get_cursor_position(&(g_dis.start_line), &(g_dis.start_offset));
	g_line.is_modified = 1;
}

void	rl_insert(int c)
{
	char s[1];

	s[0] = (char)c;
	insert_text(s, 1);
}

void	cursor_l(void)
{
	if (g_line.c_pos > 0)
		g_line.c_pos--;
}

void	cursor_r(void)
{
	if (g_line.c_pos < g_line.len)
		g_line.c_pos++;
	else
		insert_hist_compl();
}

void	cursor_d(void)
{
	if ((g_line.c_pos + g_dis.start_offset) / (g_sc.w) \
			!= g_line.len / (g_sc.w))
	{
		g_line.c_pos += g_sc.w;
		if (g_line.c_pos > g_line.len)
			g_line.c_pos = g_line.len;
	}
}
