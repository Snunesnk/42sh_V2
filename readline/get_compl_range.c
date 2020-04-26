/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_compl_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 13:28:52 by snunes            #+#    #+#             */
/*   Updated: 2020/04/26 18:22:44 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
/*
static void	adapt_range(t_data *data)
{

}
*/
void		get_exec_lim(t_data *data)
{
	int	chosen_exec_line;

	chosen_exec_line = data->chosen_exec;
	while (chosen_exec_line - data->nb_line > 0)
		chosen_exec_line -= data->nb_line;
	chosen_exec_line = chosen_exec_line % (data->nb_line + 1);
//	ft_printf("exec line: %d\n", chosen_exec_line);
	if (data->last_print == 0)
	{
		data->first_print = 1;
		data->last_print = (data->row - 1 > data->nb_line) ? data->nb_line \
						   : data->row - 1;
	}
	else if (chosen_exec_line > data->last_print)
	{
		data->first_print = chosen_exec_line - (data->row - 2);
		data->last_print = chosen_exec_line;
	}
	else if (chosen_exec_line < data->first_print)
	{
		data->first_print = chosen_exec_line;
		data->last_print = chosen_exec_line + (data->row - 2);
	}
//	ft_printf("first_print: %d, last_print: %d\n", data->first_print, data->last_print);
//	if (data->overflow)
//		adapt_range(data);
}

