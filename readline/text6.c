/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:37:02 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 16:24:52 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "shell.h"

_Bool		g_ctrl_mode = 0;

static void	switch_cbpos(void)
{
	int	tmp;

	tmp = g_line.c_pos;
	g_line.c_pos = g_line.cursor_pos;
	g_line.cursor_pos = tmp;
}

void		rl_ctrl_mode(union u_buffer u)
{
	if (g_ctrl_mode)
	{
		if (u.buf[0] == 24 && u.buf[1] == 0)
			switch_cbpos();
	}
	g_ctrl_mode ^= 1;
}

void		rl_eot(void)
{
	if (g_line.len == 0)
	{
		if (g_subprompt && !g_oneline)
		{
			g_input_break = 1;
			g_eof = 1;
			return ;
		}
		place_cursor(g_line.len);
		free(g_line.line);
		write(STDOUT_FILENO, "\n", 1);
		deprep_terminal();
		rl_clear_signals();
		exit_clean(0);
	}
	else
		rl_delete();
}
