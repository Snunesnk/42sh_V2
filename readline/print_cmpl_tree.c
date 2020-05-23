/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmpl_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:36:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 11:45:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

union u_buffer	g_bad_seq;

static int	ask_confirmation(t_data *data)
{
	union u_buffer	c;

	c.value = 'a';
	ft_dprintf(g_dis.fd, "\nDisplay all %d possibilities ? (y or n)", \
			data->nb_exec);
	g_line.is_modified = 1;
	while (ft_isprint(c.value) || ft_isspace(c.value))
	{
		c = read_key();
		if (c.value == 'y' || c.value == 'Y' || c.value == ' ' || c.value == 9)
			break ;
		if (c.value == 'n' || c.value == 'N')
			break ;
	}
	ft_putchar('\n');
	if (c.value == 'y' || c.value == 'Y' || c.value == ' ' || c.value == '\t')
		return (1);
	if (c.value != 'n' && c.value != 'N')
		g_bad_seq = c;
	ft_putstr(tgoto(g_termcaps.cm, 0, g_dis.start_line + 2));
	get_cursor_position(&(g_dis.start_line), &(g_dis.start_offset));
	g_line.cursor_pos = 0;
	display_prompt();
	update_line();
	return (0);
}

static void	restore_line(int line)
{
	int	last_line;

	if (g_dumb_term)
	{
		ft_putchar_fd('\n', g_dis.fd);
		update_dumb_line();
		return ;
	}
	last_line = g_dis.start_line + line;
	while (last_line > g_sc.height - 1)
	{
		last_line--;
		(g_dis.start_line)--;
	}
	ft_putstr_fd(tgoto(g_termcaps.cm, 0, g_dis.start_line), g_dis.fd);
	display_prompt();
	place_cursor(g_line.c_pos);
}

static void	print_compl(t_node *compl_tree, t_data *data)
{
	t_print_list	list_compl;
	int				to_print;
	int				line;

	line = 0;
	if (!(get_list_compl(&list_compl, data)))
		return ;
	ft_putstr_fd(g_termcaps.cd, g_dis.fd);
	to_print = data->first_print;
	while (data->first_print + line < data->last_print + 1 \
			&& to_print <= data->nb_exec)
	{
		if (to_print)
			list_compl = add_compl(list_compl, to_print, data, compl_tree);
		to_print += data->nb_line;
		if (to_print > data->nb_exec)
		{
			to_print = data->first_print + ++line;
			if (data->first_print + line < data->last_print + 1)
				list_compl = list_compl_add(list_compl, "\n");
		}
	}
	ft_dprintf(g_dis.fd, "%s", list_compl.content);
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
	if (data->nb_line > data->row - 1 && !ask_confirmation(data))
		return ;
	while (is_compl_char(c) && data->nb_exec > 1)
	{
		insert_compl(compl_tree, data, 0);
		place_cursor(0);
		update_line();
		fill_data(data, compl_tree);
		print_compl(compl_tree, data);
		c = read_key();
		update_exec(c, data);
	}
	if (data->nb_exec == 1)
		insert_compl(compl_tree, data, c.value);
	else if (!enter_rc(c))
		g_bad_seq = c;
	g_autocompl_on = 0;
	clear_next();
}
