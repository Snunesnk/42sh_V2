/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:25 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:13:21 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIND_H
# define BIND_H

# include "input.h"
# include "keymaps.h"

extern struct s_keymap_entry   *g_standard_keymap;
extern struct s_keymap_entry   *g_ctlx_keymap;
extern struct s_keymap_entry   *g_meta_keymap;

extern _Bool			g_ctrl_mode;
extern _Bool			g_vim_mode;
extern _Bool			g_vim_cmd;

void	insert_text(const char *string, int len);
void	clear_line(void);

void	bind_keys(void);
void	cut_prev_wd(void);
void	cut_next_wd(void);
void	clear_befline(void);
void	paste_via_input(unsigned long v);
void	clip_paste(void);
void	wd_right(void);
void	wd_left(void);
void	clear_scr(void);
void	clear_eol(void);
void	autocomplete(void);
void	rl_home(void);
void	rl_void(void);
void	rl_end(void);
void	rl_eot(void);
void	rl_delete(void);
void	rl_backspace(void);
void	rl_insert(int c);
void	cursor_l(void);
void	cursor_r(void);
void	cursor_u(void);
void	cursor_d(void);
void	history_up(void);
void	history_down(void);
void	kill_line(void);
void    rl_reversel(void);
void	rl_ctrl_mode(union u_buffer u);
void	swap_words(void);
void	vim_insert(void);
void	vim_escape(void);
void	vim_hash(void);
void	call_fc(void);
void	beg_next_wd(void);
void	beg_next_alnum(void);
void	end_next_alnum(void);
void	end_next_wd(void);

#endif
