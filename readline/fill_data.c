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
	int	area;
	int	exec_lim;

	area = data->nb_line * data->name_p_line;
	if (area != data->exec_lim)
		exec_lim = data->nb_line * (data->name_p_line - 1);
	else
		exec_lim = area;
	get_cursor_position(&column, &row);
	ft_printf("pos du cursor: [%d, %d]\n", row, column);
	return (exec_lim);
}

int		get_nb_exec(t_node *compl_tree, int nb_exec)
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

t_data	*fill_data(t_data *data, t_node *compl_tree)
{
	data->curs_col = 0;
	data->curs_row = 0;
	data->nb_line = 1;
	data->name_p_line = 0;
	data->nb_exec_sav = get_nb_exec(compl_tree, 0);
	if (data->name_l)
		data->name_p_line = data->column / data->name_l;
	if (data->name_p_line)
		data->nb_line = data->nb_exec_sav / data->name_p_line + 1;
	if (data->name_p_line > data->nb_exec_sav / data->nb_line)
	{
		if ((data->nb_exec_sav / data->nb_line) * data->nb_line \
				!= data->nb_exec_sav)
			data->name_p_line = data->nb_exec_sav / data->nb_line + 1;
		else
			data->name_p_line = data->nb_exec_sav / data->nb_line;
	}
	data->exec_lim = get_exec_lim(data);
	ft_printf("nb_exec: %d\n", data->nb_exec_sav);
	return (data);
}
