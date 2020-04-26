/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:33:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/26 18:50:25 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_node			*get_node(t_node *compl_tree, int nb_node)
{
	if (nb_node > compl_tree->nb_node)
		return (get_node(compl_tree->right, nb_node));
	else if (nb_node < compl_tree->nb_node)
		return (get_node(compl_tree->left, nb_node));
	return (compl_tree);
}

t_print_list	list_compl_add(t_print_list list_compl, char *to_add)
{
	int	i;

	i = 0;
	while (to_add[i])
	{
		list_compl.content[list_compl.used + i] = to_add[i];
		i++;
	}
	list_compl.used += i;
	return (list_compl);
}

t_print_list	*get_list_compl(t_print_list *list_compl, t_data *data)
{
	if (!(list_compl->content = (char *)ft_memalloc(sizeof(char) * \
					(data->row * data->column * 3))))
	{
		ft_printf("./21sh: cannot allocate memory\n");
		return (NULL);
	}
	list_compl->used = 0;
	list_compl->capacity = data->row * data->column * 3;
	*list_compl = list_compl_add(*list_compl, "\n");
	return (list_compl);
}

t_print_list	add_compl(t_print_list list_compl, int to_print, \
		t_data *data, t_node *compl_tree)
{
	t_node	*node_to_print;
	int		len;

	len = 0;
	node_to_print = get_node(compl_tree, to_print);
	if (to_print == data->chosen_exec)
		list_compl = list_compl_add(list_compl, "\033[47m\033[30m");
	else
		list_compl = list_compl_add(list_compl, node_to_print->color);
	list_compl = list_compl_add(list_compl, node_to_print->name);
	if (to_print != data->chosen_exec)
		list_compl = list_compl_add(list_compl, "\033[0m");
	while (node_to_print->length + len < data->name_l - 2)
	{
		list_compl = list_compl_add(list_compl, " ");
		len++;
	}
	if (to_print == data->chosen_exec)
		list_compl = list_compl_add(list_compl, "\033[0m");
	list_compl = list_compl_add(list_compl, "  ");
	return (list_compl);
}
