/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:58:12 by snunes            #+#    #+#             */
/*   Updated: 2020/05/05 19:11:13 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_input_fd(int fd)
{
	char	*input;
	int		first_iter;
	char	*last_lines;

	input = NULL;
	first_iter = 1;
	last_lines = NULL;
	while (first_iter || last_lines)
	{
		if (get_stdin(fd, &input) < 0)
			break ;
		if (input)
			input = append_line(&last_lines, input);
		first_iter = 0;
	}
	if (!input && last_lines)
		input = last_lines;
	else
		ft_memdel((void **)&last_lines);
	return (input);
}
