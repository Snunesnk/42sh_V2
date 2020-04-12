/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 22:38:56 by snunes            #+#    #+#             */
/*   Updated: 2020/04/12 23:07:07 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

void	change_binding(t_o_options **option_list, char *name)
{
	if (ft_strequ(name, "emacs"))
	{
		g_vim_mode = 1 - *((*option_list)[0].variable);
		*((*option_list)[6].variable) = g_vim_mode;
	}
	else if (ft_strequ(name, "vi"))
	{
		g_vim_mode = *((*option_list)[6].variable);
		*((*option_list)[0].variable) = 1 - g_vim_mode;
	}
	bind_keys();
}
