#include "ft_readline.h"

t_data	*init_data(void)
{
	t_data	*new_data;

	if (!(new_data = ft_memalloc(sizeof(*new_data))))
		return (NULL);
	new_data->name_l = 0;
	new_data->column = 0;
	new_data->nb_exec = 0;
	new_data->exec_lim = 0;
	new_data->start = 0;
	new_data->end = 0;
	new_data->nb_exec_sav = 0;
	new_data->type = 0;
	return (new_data);
}

void	get_cursor_position(int *column, int *row)
{
	int		a;
	char	input;

	*column = 0;
	*row = 0;
	a = 0;
	write(STDIN_FILENO, "\033[6n", 4);
	while (input != 'R')
	{
		read(STDIN_FILENO, &input, 1);
		if (input >= '0' && input <= '9')
		{
			if (a == 0)
				*row = *row * 10 + input - '0';
			else
				*column = *column * 10 + input - '0';
		}
		if (input == ';')
			a++;
	}
}

int		get_exec_lim(t_data *data)
{
	int	column;
	int	row;

	get_cursor_position(&column, &row);
	return (1);
}

t_data	*fill_data(t_data *data, t_node *compl_tree)
{
	(void)compl_tree;
	data->nb_exec = get_nb_exec(compl_tree);
	data->exec_lim = get_exec_lim(data);
	ft_printf("nb_exec: %d\n", data->nb_exec);
	return (data);
}
