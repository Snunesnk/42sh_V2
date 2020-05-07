/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 13:21:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/07 13:35:59 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	get_cursor_position(int *row, int *col)
{
	int		a;
	int		i;
	char	input[2];

	a = 0;
	i = 0;
	*row = 0;
	*col = 0;
	ft_bzero(input, 2);
	write(0, "\033[6n", 4);
	while (*input != 'R')
	{
		read(0, &input, 1);
		if (*input >= '0' && *input <= '9')
		{
			if (a == 0)
				*row = *row * 10 + ft_atoi(input);
			else
				*col = *col * 10 + ft_atoi(input);
		}
		a = (*input == ';') ? 1 : a;
		i++;
	}
	*col -= (*col) ? 1 : 0;
	*row -= (*row) ? 1 : 0;
}
