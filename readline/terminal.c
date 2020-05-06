/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:11:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 17:55:16 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_screen g_sc;
struct termios g_termios;
struct termios g_termios_backup;
struct s_termcaps g_termcaps =
{
	.bl = NULL,
	.cd = NULL,
	.clreol = NULL,
	.ch = NULL,
	.clrpag = NULL,
	.cr = NULL,
	.do1 = NULL,
	.backspace = NULL,
	.forward_char = NULL,
	.up = NULL,
	.bw = NULL,
	.am = NULL
};

struct s_term g_term =
{
	.terminal_name = NULL,
};

const struct s_termcaps_string g_tc_strings[] =
{
	{"bl", &g_termcaps.bl},
	{"cd", &g_termcaps.cd},
	{"ce", &g_termcaps.clreol},
	{"ch", &g_termcaps.ch},
	{"cl", &g_termcaps.clrpag},
	{"cr", &g_termcaps.cr},
	{"do", &g_termcaps.do1},
	{"le", &g_termcaps.backspace},
	{"nd", &g_termcaps.forward_char},
	{"up", &g_termcaps.up},
	{"bw", &g_termcaps.bw},
	{"am", &g_termcaps.am}
};

static int	check_term_capabilities(void)
{
	register int	i;

	i = 0;
	while (i < (int)NUM_TC_STRINGS)
	{
		if (tgetflag(g_tc_strings[i].var) == ERR)
			return (ERR);
		++i;
	}
	return (0);
}

static void	get_term_capabilities(void)
{
	register int i;

	i = 0;
	while (i < (int)NUM_TC_STRINGS)
	{
		*(g_tc_strings[i].value) = tgetstr((char *)g_tc_strings[i].var,
				NULL);
		++i;
	}
}

int			get_screensize(int tty)
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

void		resize_terminal(int signo)
{
	(void)signo;
	get_screensize(STDIN_FILENO);
	redisplay_after_sigwinch();
}

int			init_terminal(void)
{
	if (g_term.terminal_name == NULL)
		g_term.terminal_name = "dumb";
	if (get_screensize(STDIN_FILENO) == -1)
		return (-1);
	if (tgetent(NULL, g_term.terminal_name) <= 0)
		g_term.terminal_name = "dumb";
	if (check_term_capabilities())
	{
		ft_dprintf(STDERR_FILENO, "Terminal type '%s' is not defined in termcap database (or have too few informations) or database could not be found.\n", g_term.terminal_name);
		exit(1);
	}
	get_term_capabilities();
	bind_keys();
	return (0);
}
