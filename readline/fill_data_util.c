#include "ft_readline.h"

int	calc_left_arrow(t_data *data)
{
	int	line;

	line = data->chosen_exec % (data->nb_line + 1);
	data->chosen_exec -= data->nb_line;
	if (data->chosen_exec > 0)
		return (data->chosen_exec);
	if (line == 1)
	{
		data->chosen_exec = data->nb_line;
		while (data->chosen_exec < data->nb_exec)
			data->chosen_exec += data->nb_line;
		return (data->chosen_exec - data->nb_line);
	}
	data->chosen_exec = (line - 1) + data->nb_line * (data->name_p_line - 1);
	if (data->chosen_exec > data->nb_exec)
		data->chosen_exec -= data->nb_line;
	return (data->chosen_exec);
}
