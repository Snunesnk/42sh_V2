/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:37 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:35:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	insert_mode_first(void)
{
	g_dis.cbpos = 0;
	vim_insert();
	update_line();
}

void	replace_wd(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, sizeof(int));
	if (ft_isprint(c))
	{
		g_line.line[g_dis.cbpos] = c;
		update_line();
	}
}

void	replace_mode(void)
{
	vim_insert();
	g_replace_mode = 1;
}

void	clear_all_l(void)
{
	ft_bzero(g_line.line, g_line.len);
	g_dis.cbpos = 0;
	update_line();
	vim_insert();
}

void	c_motion(union u_buffer d)
{
	union u_buffer c;

	c.value = 0;
	read(STDIN_FILENO, c.buf, sizeof(int));
	if (c.value == d.value)
		clear_all_l();
}
