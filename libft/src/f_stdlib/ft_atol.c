/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:17:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/13 13:58:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>

#include "libft.h"
#include "ft_errno.h"

static long	overflow(long a, long b, int sign)
{
	long	maxdiv;
	long	maxmod;

	maxdiv = sign == 1 ? LONG_MAX / 10 : LONG_MIN / 10;
	maxmod = sign == 1 ? LONG_MAX % 10 : LONG_MIN % 10;
	if (a == maxdiv)
	{
		if (b <= maxmod * sign)
			return (a * 10 + (b * sign));
		else
		{
			g_errno = E_ERANGE;
			return (-1);
		}
	}
	else if ((sign == 1 && a > maxdiv) || (sign == -1 && a < maxdiv))
	{
		g_errno = E_ERANGE;
		return (-1);
	}
	return (a * 10 + (b * sign));
}

long		ft_atol(const char *str)
{
	long	nbr;
	int		i;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	g_errno = E_ERANGE;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = str[i] == '-' ? -1 : 1;
		++i;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		g_errno = 0;
		nbr = overflow(nbr,
			(str[i] ^ ((1 << 5) | (1 << 4))), sign);
		if (g_errno == E_ERANGE)
			return (-1);
		++i;
	}
	return (nbr);
}
