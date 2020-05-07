/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:11:13 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/07 15:52:02 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

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
	{"cr", &g_termcaps.cr},
	{"sf", &g_termcaps.sf},
	{"sr", &g_termcaps.sr},
	{"cm", &g_termcaps.cm}
};

static int	get_term_capabilities(char **buffer)
{
	int i;

	i = 0;
	while (i < NUM_TC_STRINGS)
	{
		*g_tc_strings[i].value = tgetstr((char *)g_tc_strings[i].var, buffer);
		if (!*g_tc_strings[i].value && !ft_strequ(g_tc_strings[i].var, "cr"))
			ft_printf("%s not supported\n", g_tc_strings[i].var);
		++i;
	}
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
	char	*buffer;

	BC = NULL;
	UP = NULL;
	if (!(buffer = (char *)ft_memalloc(sizeof(char) * 2048)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		exit(e_cannot_allocate_memory);
	}
	if (g_term.terminal_name == NULL)
		g_term.terminal_name = "dumb";
	if (get_screensize(STDIN_FILENO) == -1)
		return (-1);
	if (tgetent(buffer, g_term.terminal_name) <= 0 \
			|| !get_term_capabilities(&buffer))
	{
		ft_dprintf(STDERR_FILENO, "Terminal type '%s' is not defined in " \
				"termcap database (or have too few informations) or database " \
				"could not be found.\n", g_term.terminal_name);
		exit(1);
	}
	bind_keys();
	return (0);
}
