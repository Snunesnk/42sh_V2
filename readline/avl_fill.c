/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:40:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 14:42:58 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "error.h"

char	*extract_file_name(char *name)
{
	char	*new_name;
	int		i;

	i = ft_str_wchar_len(name) - 2;
	while (i >= 0 && name[i] != '/')
		i--;
	new_name = name + i + 1;
	return (ft_strdup(new_name));
}

int		ft_node_cmp(t_node *tree, t_node *node)
{
	if (!tree)
		return (-1);
	if (!node)
		return (1);
	return (ft_strcmp(node->name, tree->name));
}

void	update_l(t_node *node, t_data *data)
{
	struct winsize	size;
	size_t			len;

	len = ft_strlen(node->name);
	ioctl(0, TIOCGWINSZ, &size);
	data->column = size.ws_col;
	data->row = size.ws_row;
	if (len + 2 > (size_t)data->column)
	{
		data->has_overflow = 1;
		return ;
	}
	if (len + 2 > (size_t)data->name_l)
		data->name_l = ft_strlen(node->name) + 2;
}

t_node	*place_node(t_node *tree, t_node *new_node, t_data *data)
{
	int balanced;

	if (!tree)
		return (new_node);
	if (ft_strequ(tree->name, new_node->name))
	{
		free_node(new_node);
		return (tree);
	}
	if (ft_node_cmp(tree, new_node) <= 0)
		tree->left = place_node(tree->left, new_node, data);
	else
		tree->right = place_node(tree->right, new_node, data);
	tree->heigth = 1 + max(heigth(tree->left), heigth(tree->right));
	balanced = check_balance(tree);
	if (balanced < -1 || balanced > 1)
		tree = balance(balanced, tree, new_node);
	return (tree);
}

t_node	*add_node(t_node *tree, char *name, t_data *data, char *color)
{
	t_node		*node;

	if (!(node = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	if (!(node->name = extract_file_name(name)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	if (!(node->color = ft_strdup(color)))
		return (NULL);
	node->right = NULL;
	node->left = NULL;
	node->heigth = 1;
	node->length = ft_str_wchar_len(node->name);
	update_l(node, data);
	tree = place_node(tree, node, data);
	return (tree);
}
