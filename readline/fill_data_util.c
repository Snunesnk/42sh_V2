/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:38:15 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/06 19:20:53 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	calc_left_arrow(t_data *data)
{
	int	line;

	line = data->chosen_exec;
	while (line - data->nb_line > 0)
		line -= data->nb_line;
	line = data->chosen_exec % (data->nb_line + 1);
	data->chosen_exec -= data->nb_line;
	if (data->chosen_exec > 0)
		return (data->chosen_exec);
	if (line == 1)
	{
		data->chosen_exec = data->nb_line;
		while (data->chosen_exec <= data->nb_exec)
			data->chosen_exec += data->nb_line;
		return (data->chosen_exec - data->nb_line);
	}
	data->chosen_exec = (line - 1) + data->nb_line * (data->name_p_line - 1);
	while (data->chosen_exec > data->nb_exec)
		data->chosen_exec -= data->nb_line;
	return (data->chosen_exec);
}

int	ft_str_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_compl_start(void)
{
	int			start;
	static char	operator[] = "&|<>;";

	start = g_line.c_pos;
	while (start > 0 && !ft_isspace(g_line.line[start - 1]) \
				&& g_line.line[start - 1] != '/' \
				&& !ft_strchr(operator, g_line.line[start - 1]))
		start--;
	return (start);
}
