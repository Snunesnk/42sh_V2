/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymaps.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:05 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 12:18:34 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMAPS_H
# define KEYMAPS_H

# define ISFUNC 0
# define ISKMAP 1
# define ISMACR 2

struct	s_keymap_entry
{
	char	type;
	void	(*func)();
};

extern struct s_keymap_entry	g_emacs_standard_keymap[];
extern struct s_keymap_entry	g_emacs_ctlx_keymap[];
extern struct s_keymap_entry	g_emacs_meta_keymap[];
extern struct s_keymap_entry	g_vim_standard_keymap[];
extern struct s_keymap_entry	g_vim_ctlx_keymap[];
extern struct s_keymap_entry	g_vim_meta_keymap[];

#endif
