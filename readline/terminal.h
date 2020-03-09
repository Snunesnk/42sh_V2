/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:57 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/03 17:22:58 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# define NUM_TC_STRINGS (sizeof(g_tc_strings) / sizeof(struct s_termcaps_string))

struct s_termcaps
{
	char	*at7;
	char	*DC;
	char	*DO;
	char	*clrscroll;
	char	*IC;
	char	*UP;
	char	*bl;
	char	*cd;
	char	*clreol;
	char	*ch;
	char	*clrpag;
	char	*cr;
	char	*dc;
	char	*do1;
	char	*ei;
	char	*ic;
	char	*im;
	char	*kD;	/* delete */
	char	*kH;	/* home down ?? */
	char	*kI;	/* insert */
	char	*kd;
	char	*ke;	/* end keypad mode */
	char	*kh;	/* home */
	char	*kl;
	char	*kr;
	char	*ks;	/* start keypad mode */
	char	*ku;
	char	*backspace;
	char	*mm;
	char	*mo;
	char	*forward_char;
	char	*pc;
	char	*up;
	char	*visible_bell;
	char	*vs;
	char	*ve;
};

struct s_termcaps_string
{
	const char *const	var;
	char			**value;
};

/* Variables that hold the screen dimensions, used by the display code. */
struct s_screen
{
	int	w;
	int	height;
	int	chars;
};

struct s_term
{
	char	*terminal_name;
	char	*term_string_buffer;
	char	*term_buffer;
};

extern struct s_termcaps		g_termcaps;
extern struct termios			g_termios;
extern struct termios			g_termios_backup;
extern struct s_screen			g_sc;
extern struct s_term			g_term;
extern const struct s_termcaps_string	g_tc_strings[];

int	init_terminal(void);
void	rl_set_signals(void);
void	rl_clear_signals(void);
void	resize_terminal(int signo);
void	initialize(void);

#endif
