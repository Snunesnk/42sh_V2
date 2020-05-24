/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yank_vim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:26:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/24 11:16:13 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// to cut and clear eol use: void	clear_eol(void)

void	yank_eol_nocut(void)
{ // Copy end of line without cutting eol
	if (g_line.c_pos != g_line.len)
	{
		g_clip.l = g_line.len - g_line.c_pos;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
		g_line.len -= g_clip.l;
		g_line.is_modified = 1;
		update_line();
	}
}
