/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:21:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/02 18:40:31 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_stack.h"
# include "bind.h"
# include "keymaps.h"
# include "input.h"
# include "terminal.h"
# include "utils.h"
# include "display.h"
# include "line.h"
# include "tty.h"
# include "history.h"
# include "avl.h"
# include "autocomplete.h"
# include "prompt.h"

# ifndef SIGWINCH
#  define SIGWINCH 28
# endif

# define SHELL_SPECIAL_CHARS	"|&;<>()$`\\\"'*?[#˜=% \t\n"

/*
** List of colors the shell uses, END_OF_COLOR must be \033[0m
*/
# define END_OF_COLOR "\033[0m"
# define HIST_COMPL_COLOR "\033[38;5;8m"
# define G_LINE_COLOR "\033[38;5;250m"
# define PROMPT_COLOR "\033[38;5;117m"

/*
** List of special char the shell prompt uses
*/
# define GREEN_ARROW "\033[38;5;47m\u279c  \033[0m"
# define END_SIGN "\033[0m\033[38;5;231m \u00BB \033[0m"
# define RED_ARROW "\033[38;5;196m\u279c  \033[0m"

char	*ft_readline(const char *prompt);
char	*readline_loop(const char *prompt, int *qmode);
char	*get_quote(int *qmode, char *input);

#endif
