/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:37 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 19:06:28 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	insert_mode_first(void)
{
	g_line.c_pos = 0;
	vim_insert();
	g_line.is_modified = 1;
}

void	replace_wd(void)
{
	int	c;

	c = 0;
	if (read(STDIN_FILENO, &c, sizeof(int)) < 0)
		return ;
	if (ft_isprint(c))
	{
		g_line.line[g_line.c_pos] = c;
		g_line.is_modified = 1;
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
	g_line.c_pos = 0;
	vim_insert();
	g_line.is_modified = 1;
}

void	c_motion(union u_buffer d)
{
	union u_buffer c;

	c.value = 0;
	if (read(STDIN_FILENO, c.buf, sizeof(int)) < 0)
		return ;
	if (c.value == d.value)
		clear_all_l();
}
