/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:17:59 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/30 15:16:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoifd(const char *str)
{
	unsigned long	nbr;
	int				i;
	unsigned short	val;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		if (nbr > nbr * 10 + val)
			return (-1);
		nbr = nbr * 10 + val;
		++i;
	}
	return (nbr);
}
