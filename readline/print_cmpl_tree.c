#include "ft_readline.h"

void	print_compl(t_node *compl_tree, t_data *data)
{
	int	to_print;
//	int	area;

//	area = data->nb_line * data->name_p_line;
	to_print = 1;
	ft_printf("name_l: %d, nb_exec: %d\n", data->name_l, data->nb_exec);
	ft_printf("nb_line: %d, name_p_line: %d\n", data->nb_line, data->name_p_line);
	while (to_print != data->exec_lim)
	{
		if (to_print)
			print_tree(compl_tree, data, to_print);
		to_print = to_print + data->nb_line;
		if (to_print > data->nb_exec_sav)
			ft_putstr("\n");
		to_print = to_print % (data->nb_exec_sav + 1);
	}
	if (to_print)
		print_tree(compl_tree, data, to_print);
	ft_putstr("\n");
}

void	print_tree(t_node *compl_tree, t_data *data, int to_print)
{
	if (!compl_tree)
		return ;
	if (compl_tree->left && to_print < compl_tree->nb_node)
		print_tree(compl_tree->left, data, to_print);
	if (to_print == compl_tree->nb_node)
	{
		int	length;
		length = data->name_l - compl_tree->length;
		ft_printf("%s", compl_tree->name);
		while (length)
		{
			ft_putchar(' ');
			length--;
		}
	}
	if (compl_tree->right && to_print > compl_tree->nb_node)
		print_tree(compl_tree->right, data, to_print);
}
