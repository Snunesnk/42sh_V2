#include "ft_readline.h"

t_data	*init_data(void)
{
	t_data	*new_data;

	if (!(new_data = ft_memalloc(sizeof(*new_data))))
		return (NULL);
	new_data->name_l = 0;
	new_data->column = 0;
	new_data->chosen_exec = 0;
	new_data->first_print = 0;
	new_data->last_print = 0;
	new_data->nb_exec = 0;
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

void		get_exec_lim(t_data *data)
{
	int				chosen_exec_line;
	int				middle_line;

	chosen_exec_line = data->chosen_exec % data->nb_line;
	if (data->nb_line < data->row -1)
	{
		data->first_print = 1;
		data->last_print = data->nb_line;
	}
	else
	{
		middle_line = (data->row - 1) / 2;
		data->first_print = chosen_exec_line - middle_line;
		data->last_print = chosen_exec_line + middle_line;
		if (data->first_print < 1)
		{
			data->last_print -= (data->first_print - 1);
			data->first_print -= (data->first_print - 1);
		}
		if (data->last_print > data->nb_line)
		{
			data->first_print -= data->last_print - data->nb_line;
			data->last_print -= data->last_print - data->nb_line;
		}
	}
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
	data->nb_line = 1;
	data->name_p_line = 0;
	data->nb_exec = get_nb_exec(compl_tree, 0);
	if (data->name_l)
		data->name_p_line = data->column / data->name_l;
	if (data->name_p_line)
		data->nb_line = data->nb_exec / data->name_p_line + 1;
	if (data->name_p_line > data->nb_exec / data->nb_line)
	{
		if ((data->nb_exec / data->nb_line) * data->nb_line \
				!= data->nb_exec)
			data->name_p_line = data->nb_exec / data->nb_line + 1;
		else
			data->name_p_line = data->nb_exec / data->nb_line;
	}
	get_exec_lim(data);
	ft_printf("nb_exec: %d\n", data->nb_exec);
	return (data);
}
