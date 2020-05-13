/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 13:21:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/13 19:51:22 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	get_first_input(void)
{
	char	input[2];

	input[0] = 0;
	input[1] = 0;
	read(0, &input, 1);
	while (*input != 27)
		read(0, &input, 1);
	return (*input);
}

void	get_cursor_position(int *row, int *col)
{
	int		a;
	int		i;
	char	input[2];

	a = 0;
	i = 0;
	*row = 0;
	*col = 0;
	write(0, "\033[6n", 4);
	*input = get_first_input();
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
