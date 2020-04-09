/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmpl_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:36:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:36:57 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int				g_autocompl_query = -1;
union u_buffer	g_autocompl_bad_seq;

int		ask_confirmation(t_data *data)
{
	char	c;

	c = 'a';
	ft_printf("\nDisplay all %d possibilities ? (y or n)", data->nb_exec);
	while (ft_isprint(c) || ft_isspace(c))
	{
		read(STDIN_FILENO, &c, 1);
		if (c == 'y' || c == 'Y' || c == ' ')
		{
			ft_putchar('\n');
			return (1);
		}
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

	line = 0;
	to_print = data->first_print;
	ft_putstr("\n");
	while (data->first_print + line < data->last_print + 1)
	{
		if (to_print)
			print_tree(compl_tree, data, to_print);
		to_print += data->nb_line;
		if (to_print > data->nb_exec)
		{
			line++;
			to_print = data->first_print + line;
			if (data->first_print + line < data->last_print + 1)
				ft_putstr("\n");
		}
	}
	ft_putstr(g_termcaps.cd);
	ft_putstr(tgoto(g_termcaps.gup, 0, line));
	update_line();
}

void	print_tree(t_node *compl_tree, t_data *data, int to_print)
{
	int	len;

	if (!compl_tree)
		return ;
	if (compl_tree->left && to_print < compl_tree->nb_node)
		print_tree(compl_tree->left, data, to_print);
	if (to_print == compl_tree->nb_node)
	{
		if (to_print == data->chosen_exec)
			ft_printf("\033[47m\033[30m%s", compl_tree->name);
		else
			ft_printf("%s", compl_tree->name);
		len = data->name_l - compl_tree->length - 2;
		while (len > 0)
		{
			write(STDOUT_FILENO, SPACES, len);
			len -= 60;
		}
		if (to_print == data->chosen_exec)
			ft_putstr("\033[0m");
		ft_putstr("  ");
	}
	if (compl_tree->right && to_print > compl_tree->nb_node)
		print_tree(compl_tree->right, data, to_print);
}

int		is_compl_char(union u_buffer c)
{
	if (c.value == 10000)
		return (-1);
	if (c.buf[0] == 27 && c.buf[1] == '[' && c.buf[2] && !c.buf[3])
	{
		if (c.buf[2] == 'A' || c.buf[2] == 'B' || c.buf[2] == 'C'\
				|| c.buf[2] == 'D')
			return (1);
		return (0);
	}
	if (c.value == 9)
		return (1);
	return (0);
}

void	display_compl(t_node *compl_tree, t_data *data)
{
	union u_buffer	c;

	c.value = 10000;
	g_autocompl_bad_seq.value = 0;
	fill_data(data, compl_tree);
	data->compl_start = get_compl_start();
	if (data->nb_exec >= 100 && !ask_confirmation(data))
		return ;
	while (is_compl_char(c) && data->nb_exec > 1)
	{
		print_compl(compl_tree, data);
		insert_compl(compl_tree, data);
		c = read_key();
		update_exec(c, data);
		fill_data(data, compl_tree);
	}
	if (data->nb_exec == 1)
		insert_compl(compl_tree, data);
	else if (!enter_rc(c))
		g_autocompl_bad_seq = c;
	if (!enter_rc(c))
		insert_text(" ", 1);
	ft_putstr(g_termcaps.cd);
	update_line();
}
