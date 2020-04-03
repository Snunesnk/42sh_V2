#include "ft_readline.h"

void	print_compl(t_node *compl_tree, t_data *data)
{
	int	to_print;
	int	line;

	ft_putstr(g_termcaps.cd);
	line = 0;
	to_print = data->first_print;
//	ft_printf("name_l: %d, chosen_exec: %d\n", data->name_l, data->chosen_exec);
//	ft_printf("nb_line: %d, name_p_line: %d\n", data->nb_line, data->name_p_line);
//	ft_printf("first print: %d, last_print: %d\n", data->first_print, data->last_print);
	while (line < data->last_print)
	{
//		ft_printf("to_print: %d\n", to_print);
		if (to_print)
			print_tree(compl_tree, data, to_print);
		to_print = to_print + data->nb_line;
//		ft_printf("to_print: %d\n", to_print);
		if (to_print > data->nb_exec)
		{
			line++;
			to_print = data->first_print + line;
			if (line < data->last_print)
				ft_putstr("\n");
		}
	}
	ft_putstr(tgoto(g_termcaps.gup, 0, line));
	update_line();
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
