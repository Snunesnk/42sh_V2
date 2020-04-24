/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 13:21:12 by snunes            #+#    #+#             */
/*   Updated: 2020/04/24 13:48:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	get_start_offset(void)
{
	int		a = 0;
	int		i = 0;
	int		rows;
	char	input[2];

	g_dis.start_offset = 0;
	rows = 0;
	*input = 0;
	write(0, "\033[6n", 4);
	while (*input != 'R')
	{
		read(0, &input, 1);
		if (*input >= '0' && *input <= '9')
		{
			if (a == 0)
				rows = rows * 10 + ft_atoi(input);
			else
				g_dis.start_offset = g_dis.start_offset * 10 + ft_atoi(input);
		}
		if (*input == ';')
			a++;
		i++;
	}
	if (g_dis.start_offset)
		g_dis.start_offset -= 1;
}
