#include "ft_readline.h"

int		g_autocompl_query = -1;

int		ask_confirmation(t_data *data)
{
	char	c;

	c = 'a';
	ft_printf("\nDisplay all %d possibilities ? (y or n)", data->nb_exec);
	while (ft_isprint(c) || ft_isspace(c))
	{
		read(STDIN_FILENO, &c, 1);
		if (c == 'y' || c == 'Y' || c == ' ')
			return (1);
		if (c == 'n' || c == 'N')
		{
			update_line();
			return (0);
		}
	}
	g_autocompl_query = c;
	update_line();
	return (0);
}

void	print_compl(t_node *compl_tree, t_data *data)
{
	int	to_print;
	int	line;

	ft_putstr(g_termcaps.cd);
	line = 0;
	to_print = data->first_print;
	if (data->nb_exec >= 100 && !ask_confirmation(data))
		return ;
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
		if (to_print == data->chosen_exec)
			ft_printf("\033[47m\033[30m%s", compl_tree->name);
		else
			ft_printf("%s", compl_tree->name);
		while (length)
		{
			if (length == 2 && to_print == data->chosen_exec)
				ft_putstr("\033[0m");
			ft_putchar(' ');
			length--;
		}
	}
	if (compl_tree->right && to_print > compl_tree->nb_node)
		print_tree(compl_tree->right, data, to_print);
}
