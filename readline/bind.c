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

struct s_keymap_entry	*g_keymap;

void	bind_keys(struct s_keymap_entry *keymap)
{
	g_keymap = keymap;
}
