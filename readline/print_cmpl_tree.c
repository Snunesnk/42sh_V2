/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmpl_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:36:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 23:32:34 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

union u_buffer	g_bad_seq;

static int	ask_confirmation(t_data *data)
{
	union u_buffer	c;

	c.value = 'a';
	ft_printf("\nDisplay all %d possibilities ? (y or n)", data->nb_exec);
	while (ft_isprint(c.value) || ft_isspace(c.value))
	{
		c = read_key();
		if (c.value == 'y' || c.value == 'Y' || c.value == ' ')
		{
			ft_putchar('\n');
			return (1);
		}
		if (c.value == 'n' || c.value == 'N')
		{
			update_line();
			return (0);
		}
	}
	g_bad_seq = c;
	update_line();
	return (0);
}

static void	restore_line(int line)
{
	ft_putstr(g_termcaps.cd);
	if (line)
		ft_putstr(tgoto(g_termcaps.gup, 0, line));
	update_line();
}

static void	print_compl(t_node *compl_tree, t_data *data)
{
	t_print_list	list_compl;
	int				to_print;
	int				line;

	line = 0;
	if (!(get_list_compl(&list_compl, data)))
		return ;
	ft_putstr(g_termcaps.cd);
	to_print = data->first_print;
	while (data->first_print + line < data->last_print + 1)
	{
		if (to_print)
			list_compl = add_compl(list_compl, to_print, data, compl_tree);
		to_print += data->nb_line;
		if (to_print > data->nb_exec)
		{
			line++;
			to_print = data->first_print + line;
			if (data->first_print + line < data->last_print + 1)
				list_compl = list_compl_add(list_compl, "\n");
		}
	}
	ft_printf("%s%s", list_compl.content, g_termcaps.cd);
	free(list_compl.content);
	restore_line(data->overflow + line);
}

static int	is_compl_char(union u_buffer c)
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

void		display_compl(t_node *compl_tree, t_data *data)
{
	union u_buffer	c;

	c.value = 10000;
	g_bad_seq.value = 0;
	fill_data(data, compl_tree);
	data->compl_start = get_compl_start();
	if (data->nb_exec >= 100 && !ask_confirmation(data))
		return ;
	while (is_compl_char(c) && data->nb_exec > 1)
	{
		insert_compl(compl_tree, data);
		print_compl(compl_tree, data);
		c = read_key();
		update_exec(c, data);
		fill_data(data, compl_tree);
	}
	if (data->nb_exec == 1)
		insert_compl(compl_tree, data);
	else if (!enter_rc(c))
		g_bad_seq = c;
	if (!enter_rc(c) && c.value != ' ' && g_line.line[g_dis.cbpos - 1] != '/')
		insert_text(" ", 1);
	restore_line((g_dis.prompt_l + g_line.len) / data->column);
}
