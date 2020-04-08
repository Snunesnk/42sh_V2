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
		while (data->chosen_exec < data->nb_exec)
			data->chosen_exec += data->nb_line;
		return (data->chosen_exec - data->nb_line);
	}
	data->chosen_exec = (line - 1) + data->nb_line * (data->name_p_line - 1);
	if (data->chosen_exec > data->nb_exec)
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
