/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:23:05 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 11:42:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	prep_terminal(void)
{
	tcgetattr(STDIN_FILENO, &g_termios);
	tcgetattr(STDIN_FILENO, &g_termios_backup);
	g_termios.c_lflag &= ~(ICANON | ECHO);
	g_termios.c_lflag &= ~ISIG;
	g_termios.c_cc[VMIN] = 1;
	g_termios.c_cc[VTIME] = 0;
	g_termios.c_iflag &= ~(ICRNL | INLCR);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_termios);
}

void	deprep_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_termios_backup);
}
