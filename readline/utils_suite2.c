/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_suite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:03:17 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:03:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	mvctrlkey(union u_buffer c)
{
	return (c.buf[2] == 49 && c.buf[3] == 59 && c.buf[4] == 53);
}

int	enter_rc(union u_buffer c)
{
	return (c.buf[0] == 13 && c.buf[1] == 0);
}
