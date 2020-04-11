/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:33:11 by snunes            #+#    #+#             */
/*   Updated: 2020/04/11 17:11:59 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <sys/types.h>
#include <sys/stat.h>

static char	*get_sp_color(struct stat st)
{
	static char	*(color[6]) = {"\033[01;32m", "\033[1;34m", "\033[37;41m", \
		"\033[30;43m", "\033[30;42m", "\033[34;42m"};

	if (S_IFDIR & st.st_mode)
	{
		if (S_IWOTH & st.st_mode && 000100 & st.st_mode)
			return (color[4]);
		else if (S_IWOTH & st.st_mode)
			return (color[5]);
		return (color[1]);
	}
	if (S_ISUID & st.st_mode)
		return (color[2]);
	if (S_ISGID & st.st_mode)
		return (color[3]);
	return (color[0]);
}

char	*get_color(char *file)
{
	static char	*(color[8]) = {"\033[37m",  "\033[40;33;01m", \
		"\033[40;33;01m", "\033[40;33m", "\033[1;36m", "\033[1;35m"};
	struct stat	st;

	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (get_sp_color(st));
	if (S_ISCHR(st.st_mode))
		return (color[1]);
	if (S_ISBLK(st.st_mode))
		return (color[2]);
	if (S_ISFIFO(st.st_mode))
		return (color[3]);
	if (S_ISLNK(st.st_mode))
		return (color[4]);
	if (S_ISSOCK(st.st_mode))
		return (color[5]);
	if (S_ISREG(st.st_mode))
	{
		ft_printf("file: %s, st.st_mode: %d", file, st.st_mode);
		if (is_exec(file))
			return (get_sp_color(st));
		return (color[0]);
	}
	return ("\033[33m");
}

static t_node	*get_node(t_node *compl_tree, int nb_node)
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
