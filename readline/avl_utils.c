/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:38:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 13:49:34 by snunes           ###   ########.fr       */
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

int		is_inhib(char c)
{
	if (c == '"' || c == '\'' || c == '\\')
		return (1);
	return (0);
}

int		count_inhib(char *str)
{
	int	i;
	int	nb_inhib;

	i = 0;
	nb_inhib = 0;
	while (str[i])
	{
		if (is_inhib(str[i]))
			nb_inhib++;
		i++;
	}
	return (nb_inhib);
}
