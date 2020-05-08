/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:11:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 21:55:19 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

int				g_dumb_term = 0;
struct s_screen g_sc;
struct termios g_termios;
struct termios g_termios_backup;
struct s_termcaps g_termcaps =
{
	.bl = NULL,
	.cd = NULL,
	.clreol = NULL,
	.clrpag = NULL,
	.cr = NULL,
	.sf = NULL,
	.sr = NULL,
	.cm = NULL
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
	{"cl", &g_termcaps.clrpag},
	{"sf", &g_termcaps.sf},
	{"sr", &g_termcaps.sr},
	{"cm", &g_termcaps.cm},
	{"cr", &g_termcaps.cr}
};

static int	get_term_capabilities(char **buffer)
{
	int i;

	i = 0;
	while (i < NUM_TC_STRINGS)
	{
		*g_tc_strings[i].value = tgetstr((char *)g_tc_strings[i].var, buffer);
		if (!*g_tc_strings[i].value)
			g_dumb_term = 1;
		++i;
	}
	i = 0;
	if (g_dumb_term && !ft_strequ("dumb", g_term.terminal_name))
		ft_printf("Termcaps capability is insuficient for normal use, " \
				"enter dumb mode.\n");
	return (1);
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
	char	buffer[2048];

	ft_bzero(buffer, 2048);
	BC = NULL;
	UP = NULL;
	if (g_term.terminal_name == NULL)
		g_term.terminal_name = "dumb";
	if (get_screensize(STDIN_FILENO) == -1)
		return (-1);
	tgetent(buffer, g_term.terminal_name);
	get_term_capabilities((char **)&buffer);
	bind_keys();
	return (0);
}
