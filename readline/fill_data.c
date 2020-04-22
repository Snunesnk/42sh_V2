/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:37:53 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 22:33:34 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		update_exec(union u_buffer c, t_data *data)
{
	if (c.value == 9 || c.value == ARROW_DOWN)
	{
		if (data->chosen_exec + 1 > data->nb_exec)
			data->chosen_exec = 1;
		else
			data->chosen_exec += 1;
	}
	else if (c.value == ARROW_UP)
	{
		data->chosen_exec -= 1;
		if (data->chosen_exec < 1)
			data->chosen_exec = data->nb_exec;
	}
	else if (c.value == ARROW_LEFT)
		data->chosen_exec = calc_left_arrow(data);
	else if (c.value == ARROW_RIGHT)
	{
		data->chosen_exec += data->nb_line;
		if (data->chosen_exec > data->nb_exec)
			data->chosen_exec = data->chosen_exec % data->nb_line + 1;
	}
}

t_data		*init_data(void)
{
	t_data	*new_data;

	if (!(new_data = ft_memalloc(sizeof(*new_data))))
		return (NULL);
	new_data->name_l = 0;
	new_data->column = 0;
	new_data->chosen_exec = 1;
	new_data->first_print = 0;
	new_data->last_print = 0;
	new_data->nb_exec = 0;
	new_data->compl_start = 0;
	new_data->overflow = 0;
	return (new_data);
}

void		get_exec_lim(t_data *data)
{
	int	chosen_exec_line;
	int	middle_line;

	chosen_exec_line = data->chosen_exec;
	while (chosen_exec_line - data->nb_line > 0)
		chosen_exec_line -= data->nb_line;
	chosen_exec_line = chosen_exec_line % (data->nb_line + 1);
	middle_line = data->row / 2;
	data->first_print = chosen_exec_line - middle_line + 2;
	if (data->first_print < 1)
		data->first_print = 1;
	data->last_print = data->first_print + data->row - 2;
	if (data->last_print > data->nb_line)
	{
		data->first_print -= data->last_print - data->nb_line;
		if (data->first_print < 1)
			data->first_print = 1;
		data->last_print = data->nb_line;
	}
	while (data->last_print + data->overflow > data->row - 1)
		data->last_print--;
}

int			get_nb_exec(t_node *compl_tree, int nb_exec)
{
	if (!compl_tree)
		return (0);
	if (compl_tree->left)
		nb_exec = get_nb_exec(compl_tree->left, nb_exec);
	nb_exec += 1;
	compl_tree->nb_node = nb_exec;
	if (compl_tree->right)
		nb_exec = get_nb_exec(compl_tree->right, nb_exec);
	return (nb_exec);
}

t_data		*fill_data(t_data *data, t_node *compl_tree)
{
	data->nb_line = 1;
	data->name_p_line = 0;
	data->column = g_sc.w;
	data->row = g_sc.height;
	data->nb_exec = get_nb_exec(compl_tree, 0);
	if (data->name_l)
		data->name_p_line = data->column / data->name_l;
	if (data->name_p_line)
		data->nb_line = data->nb_exec / data->name_p_line;
	if (data->nb_line * data->name_p_line != data->nb_exec)
		data->nb_line += 1;
	if (data->overflow)
	{
		data->nb_line = data->nb_exec;
		data->name_p_line = 1;
	}
	get_exec_lim(data);
	return (data);
}
