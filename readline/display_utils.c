/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 13:21:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/19 14:13:05 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	get_first_input(void)
{
	char	input;

	read(0, &input, 1);
	while (input != 27)
		read(0, &input, 1);
	return (input);
}

void		get_cursor_position(int *row, int *col)
{
	int		a;
	char	input[2];

	input[1] = 0;
	a = 0;
	*row = 0;
	*col = 0;
	write(STDIN_FILENO, "\033[6n", 4);
	input[0] = get_first_input();
	while (*input != 'R')
	{
		read(0, input, 1);
		if (*input >= '0' && *input <= '9')
		{
			if (a == 0)
				*row = *row * 10 + ft_atoi(input);
			else
				*col = *col * 10 + ft_atoi(input);
		}
		a = (*input == ';') ? 1 : a;
	}
	*col -= (*col) ? 1 : 0;
	*row -= (*row) ? 1 : 0;
}
