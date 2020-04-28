/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim_keymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:35:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/28 13:57:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_keymap_entry g_vim_standard_insert_keymap[] =
{
	[ 0 ... 2 ] = { ISFUNC, rl_void },
	{ ISFUNC, kill_line },
	{ ISFUNC, rl_eot },
	[ 5 ... 8 ] = { ISFUNC, rl_void },
	{ ISFUNC, autocomplete },
	[ 10 ... 22 ] = { ISFUNC, rl_void },
	{ ISFUNC, cut_prev_wd },
	[ 24 ... 26 ] = { ISFUNC, rl_void },
	{ ISKMAP, vim_escape },
	[ 28 ... 31 ] = { ISFUNC, rl_void },
	[ ' ' ... '~' ] = { ISFUNC, rl_insert },
	{ ISFUNC, rl_backspace }
};

struct s_keymap_entry g_vim_ctlx_insert_keymap[] =
{
	[ 0 ... 50 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_delete },
	[ 52 ... 64 ] = { ISFUNC, rl_void },
	{ ISFUNC, history_up },
	{ ISFUNC, history_down },
	{ ISFUNC, cursor_r },
	{ ISFUNC, cursor_l },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_end },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 73 ... 84 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_u },
	{ ISFUNC, cursor_d },
	{ ISFUNC, wd_right },
	{ ISFUNC, wd_left },
	[ 89 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_meta_insert_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_standard_cmd_keymap[] =
{
	[ 0 ... 2 ] = { ISFUNC, rl_void },
	{ ISFUNC, kill_line },
	{ ISFUNC, rl_eot },
	[ 5 ... 31 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_r },
	[ 33 ... 34 ] = { ISFUNC, rl_void },
	{ ISFUNC, vim_hash },
	{ ISFUNC, rl_end },
	[ 37 ... 47 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 49 ... 58 ] = { ISFUNC, rl_void },
	{ ISFUNC, last_goto },
	[ 60 ... 64 ] = { ISFUNC, rl_void },
	{ ISFUNC, insert_mode_last },
	{ ISFUNC, wd_left },
	{ ISFUNC, cmaj_motion },
	{ ISFUNC, dmaj_motion },
	{ ISFUNC, end_next_wd },
	{ ISFUNC, goto_chr_left },
	[ 71 ... 72 ] = { ISFUNC, rl_void },
	{ ISFUNC, insert_mode_first },
	[ 74 ... 79 ] = { ISFUNC, rl_void },
	{ ISFUNC, paste_all_r },
	{ ISFUNC, rl_void },
	{ ISFUNC, replace_mode },
	{ ISFUNC, clear_all_l },
	{ ISFUNC, goto_pchr_left },
	{ ISFUNC, undo_lastb },
	{ ISFUNC, rl_void },
	{ ISFUNC, beg_next_wd },
	{ ISFUNC, rl_backspace },
	{ ISFUNC, yank_eol },
	[ 90 ... 93 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 95 ... 96 ] = { ISFUNC, rl_void },
	{ ISFUNC, insert_mode_next },
	{ ISFUNC, beg_last_alnum },
	{ ISFUNC, c_motion },
	{ ISFUNC, d_motion },
	{ ISFUNC, end_next_alnum },
	{ ISFUNC, goto_chr_right },
	{ ISFUNC, rl_void },
	{ ISFUNC, cursor_l },
	{ ISFUNC, vim_insert },
	{ ISFUNC, history_down },
	{ ISFUNC, history_up },
	{ ISFUNC, cursor_r },
	[ 109 ... 111 ] = { ISFUNC, rl_void },
	{ ISFUNC, paste_all_l },
	{ ISFUNC, rl_void },
	{ ISFUNC, replace_wd },
	{ ISFUNC, rl_void },
	{ ISFUNC, goto_pchr_right },
	{ ISFUNC, undo_last },
	{ ISFUNC, call_fc },
	{ ISFUNC, beg_next_alnum },
	{ ISFUNC, rl_delete },
	{ ISFUNC, yank_c },
	[ 122 ... 123 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 125 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_ctlx_cmd_keymap[] =
{
	[ 0 ... 64 ] = { ISFUNC, rl_void },
	{ ISFUNC, history_up },
	{ ISFUNC, history_down },
	{ ISFUNC, cursor_r },
	{ ISFUNC, cursor_l },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_end },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 73 ... 84 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_u },
	{ ISFUNC, cursor_d },
	{ ISFUNC, wd_right },
	{ ISFUNC, wd_left },
	[ 89 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_meta_cmd_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void }
};
