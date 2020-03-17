/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:20 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 11:56:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_keymap_entry	*g_standard_keymap;
struct s_keymap_entry	*g_ctlx_keymap;
struct s_keymap_entry	*g_meta_keymap;

_Bool			g_vim_mode = 1;
_Bool			g_vim_cmd = 0;

void	bind_keys(void)
{
	if (g_vim_mode)
	{
		g_vim_cmd = 0;
		g_standard_keymap = g_vim_standard_insert_keymap;
		g_ctlx_keymap = g_vim_ctlx_insert_keymap;
		g_meta_keymap = g_vim_meta_insert_keymap;
	}
	else
	{
		g_standard_keymap = g_emacs_standard_keymap;
		g_ctlx_keymap = g_emacs_ctlx_keymap;
		g_meta_keymap = g_emacs_meta_keymap;
	}
}

void	vim_escape(void)
{
	g_vim_cmd = 1;
	g_standard_keymap = g_vim_standard_cmd_keymap;
	g_ctlx_keymap = g_vim_ctlx_cmd_keymap;
	g_meta_keymap = g_vim_meta_cmd_keymap;
}

void	vim_insert(void)
{
	g_vim_cmd = 0;
	g_standard_keymap = g_vim_standard_insert_keymap;
	g_ctlx_keymap = g_vim_ctlx_insert_keymap;
	g_meta_keymap = g_vim_meta_insert_keymap;
}
