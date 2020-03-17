/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:11:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:01:07 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_screen g_sc;
struct s_termcaps g_termcaps = {0};
struct termios g_termios;
struct termios g_termios_backup;

struct s_term g_term =
{
	.terminal_name = NULL,
	.term_string_buffer = NULL,
	.term_buffer = NULL,
};

const struct s_termcaps_string g_tc_strings[] =
{
	{"DO", &g_termcaps.gdo},
	{"UP", &g_termcaps.gup},
	{"bl", &g_termcaps.bl},
	{"cd", &g_termcaps.cd},
	{"ce", &g_termcaps.clreol},
	{"ch", &g_termcaps.ch},
	{"cl", &g_termcaps.clrpag},
	{"cr", &g_termcaps.cr},
	{"do", &g_termcaps.do1},
	{"le", &g_termcaps.backspace},
	{"nd", &g_termcaps.forward_char},
	{"up", &g_termcaps.up}
};

void	get_term_capabilities(char **bp)
{
	register int i;

	i = 0;
	while (i < (int)NUM_TC_STRINGS)
	{
		*(g_tc_strings[i].value) = tgetstr((char *)g_tc_strings[i].var,
				bp);
		++i;
	}
}

int		get_screensize(int tty)
{
	struct winsize	window_size;

	if (ioctl(tty, TIOCGWINSZ, &window_size) == -1)
	{
		window_size.ws_col = tgetnum("co");
		window_size.ws_row = tgetnum("li");
	}
	g_sc.w = window_size.ws_col;
	g_sc.height = window_size.ws_row;
	g_sc.chars = g_sc.w * g_sc.height;
	return (0);
}

void	resize_terminal(int signo)
{
	(void)signo;
	get_screensize(STDIN_FILENO);
	redisplay_after_sigwinch();
}

int		init_terminal(void)
{
	char *buffer;

	if (g_term.terminal_name == NULL)
		g_term.terminal_name = "xterm-256color";
	if (get_screensize(STDIN_FILENO) == -1)
		return (-1);
	if (g_term.term_string_buffer == NULL)
		g_term.term_string_buffer = (char*)malloc(2032);
	if (g_term.term_buffer == NULL)
		g_term.term_buffer = (char*)malloc(4080);
	if (tgetent(g_term.term_buffer, g_term.terminal_name) <= 0)
	{
		if (g_term.term_string_buffer)
			free(g_term.term_string_buffer);
		if (g_term.term_buffer)
			free(g_term.term_buffer);
		g_term.term_buffer = NULL;
		g_term.term_string_buffer = NULL;
		return (-1);
	}
	buffer = g_term.term_string_buffer;
	get_term_capabilities(&buffer);
	bind_keys();
	return (0);
}
