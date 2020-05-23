/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 17:34:10 by snunes            #+#    #+#             */
/*   Updated: 2020/05/23 17:45:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	goto_n_char(void)
{
	g_line.c_pos = g_vim_cmd_count;
	if (g_line.c_pos > g_line.len)
		g_line.c_pos = g_line.len;
}
