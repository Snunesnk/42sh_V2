/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:20 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/25 13:37:06 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_keymap_entry	*g_standard_keymap;
struct s_keymap_entry	*g_ctlx_keymap;
struct s_keymap_entry	*g_meta_keymap;

_Bool			g_vim_mode = 0;
_Bool			g_vim_cmd = 0;
_Bool			g_replace_mode = 0;
_Bool			g_got_input = 0;
int			g_c = 0;
void			*g_last_goto_f = &goto_pchr_right;
void			*g_last_goto_b = &goto_pchr_left;

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
	g_replace_mode = 0;
	if (g_line.c_pos > 0)
		--g_line.c_pos;
	update_line();
	g_standard_keymap = g_vim_standard_cmd_keymap;
	g_ctlx_keymap = g_vim_ctlx_cmd_keymap;
	g_meta_keymap = g_vim_meta_cmd_keymap;
}

void	vim_insert(void)
{
	add_back();
	g_input_break = 0;
	g_vim_cmd = 0;
	g_replace_mode = 0;
	g_standard_keymap = g_vim_standard_insert_keymap;
	g_ctlx_keymap = g_vim_ctlx_insert_keymap;
	g_meta_keymap = g_vim_meta_insert_keymap;
}

void	add_back(void)
{
	struct s_line_state	*prev;

	if (g_back && !ft_strcmp(((struct s_line_state*)g_back->data)->line, \
				g_line.line))
		return ;
	prev = ft_memalloc(sizeof(struct s_line_state));
	prev->size_buf = g_line.size_buf;
	prev->len = g_line.len;
	prev->line = ft_strndup(g_line.line, g_line.size_buf);
	prev->c_pos = g_line.c_pos;
	prev->cursor_pos = g_line.cursor_pos;
	prev->is_modified = 1;
	stack_push(&g_back, prev);
}
