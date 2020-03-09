/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:23:14 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/03 17:23:16 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	output(int c)
{
	if (write(STDOUT_FILENO, &c, sizeof(int)) != sizeof(int))
		return (0);
	return (1);
}

int		rl_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c ^ (1 << 5));
	return (c);
}

int		rl_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c | (1 << 5));
	return (c);
}

int		isoctal(int c)
{
	return (c >= '0' && c <= '7');
}

int		isxdigit(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
			|| (c >= 'A' && c <= 'F'));
}
