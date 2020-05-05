/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:17:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/05 11:44:02 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>

#include "libft.h"
#include "ft_errno.h"

static long	overflow(int sign, long a, long b)
{
	if (sign < 0)
	{
		if (a >= LONG_MIN + b)
			return (a - b);
		else
		{
			g_errno = E_EOVERFLOW;
			return (-1);
		}
	}
	else
	{
		if (a > LONG_MAX - b)
		{
			g_errno = E_EOVERFLOW;
			return (-1);
		}
		else
			return (a + b);
	}
}

long		ft_atol(const char *str)
{
	long	nbr;
	int		i;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	g_errno = E_EINVAL;
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
		nbr = overflow(sign, nbr * 10,
			(str[i] ^ ((1 << 5) | (1 << 4))));
		if (g_errno == E_EOVERFLOW)
			return (-1);
		++i;
	}
	return (nbr);
}
