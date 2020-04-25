/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_suite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:03:17 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/25 17:03:31 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	mvctrlkey(union u_buffer c)
{
	return (c.buf[2] == 49 && c.buf[3] == 59 && c.buf[4] == 53);
}

int	enter_rc(union u_buffer c)
{
	if (c.buf[0] == 13 && c.buf[1] == 0)
	{
		if (!g_autocompl_on)
			g_cursor.v_pos = 0;
		return (1);
	}
	return (0);
}
