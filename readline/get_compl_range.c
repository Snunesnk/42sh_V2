/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_compl_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 13:28:52 by snunes            #+#    #+#             */
/*   Updated: 2020/04/26 21:46:45 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	adapt_prev_range(t_data *data, t_node *compl_tree, int taken_lines)
{
	t_node	*node;
	int		ret;
	int		wanted_node;

	if (data->first_print < 1)
		data->first_print = 1;
	data->overflow = 0;
	wanted_node = data->chosen_exec;
	node = get_node(compl_tree, wanted_node);
	while (wanted_node >= data->first_print)
	{
		if (!(node = get_node(compl_tree, wanted_node)))
			break ;
		if (node->length + 2 > data->column)
		{
			ret = (node->length + 2) / data->column;
			data->overflow += ret;
			if (data->last_print - data->first_print + data->overflow \
					> data->row - taken_lines - 1)
				data->first_print += ret;
		}
		wanted_node--;
	}
	if (data->first_print > data->last_print)
		data->first_print = data->last_print;
}

static void	adapt_next_range(t_data *data, t_node *compl_tree, int taken_lines)
{
	t_node	*node;
	int		ret;
	int		wanted_node;

	if (data->last_print > data->nb_line)
		data->last_print = data->nb_line;
	data->overflow = 0;
	wanted_node = data->chosen_exec;
	node = get_node(compl_tree, wanted_node);
	while (wanted_node <= data->last_print)
	{
		if (!(node = get_node(compl_tree, wanted_node)))
			break ;
		if (node->length + 2 > data->column)
		{
			ret = (node->length + 2) / data->column;
			data->overflow += ret;
			if (data->last_print - data->first_print + data->overflow \
					> data->row - taken_lines - 1)
				data->last_print -= ret;
		}
		wanted_node++;
	}
	if (data->last_print < data->first_print)
		data->last_print = data->first_print;
}

static void	get_lines(int *chosen_exec_line, int *taken_lines, t_data *data)
{
	*taken_lines = (g_dis.prompt_l + g_line.len) / data->column;
	if (!*taken_lines)
		(*taken_lines)++;
	*chosen_exec_line = data->chosen_exec;
	while (*chosen_exec_line - data->nb_line > 0)
		*chosen_exec_line -= data->nb_line;
	*chosen_exec_line = *chosen_exec_line % (data->nb_line + 1);
}

void		get_exec_lim(t_data *data, t_node *compl_tree)
{
	int	chosen_exec_line;
	int	taken_lines;

	chosen_exec_line = 0;
	taken_lines = 0;
	get_lines(&chosen_exec_line, &taken_lines, data);
	if (data->last_print == 0)
	{
		data->first_print = 1;
		data->last_print = (data->row - 1 > data->nb_line) ? data->nb_line \
						   : data->row - taken_lines;
		adapt_next_range(data, compl_tree, taken_lines);
	}
	else if (chosen_exec_line > data->last_print)
	{
		data->first_print = chosen_exec_line - (data->row - 1 - taken_lines);
		data->last_print = chosen_exec_line;
		adapt_prev_range(data, compl_tree, taken_lines);
	}
	else if (chosen_exec_line < data->first_print)
	{
		data->first_print = chosen_exec_line;
		data->last_print = chosen_exec_line + (data->row - 1 - taken_lines);
		adapt_next_range(data, compl_tree, taken_lines);
	}
}
