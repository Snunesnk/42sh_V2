/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:38:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 22:55:18 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node(node->left);
	free(node->name);
	free(node->color);
	if (node->right)
		free_node(node->right);
	free(node);
}

int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
