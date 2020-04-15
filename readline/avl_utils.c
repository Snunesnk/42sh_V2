/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:38:29 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 15:13:56 by yforeau          ###   ########.fr       */
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

int		is_shell_spec(char c)
{
	return (!!ft_strchr(SHELL_SPECIAL_CHARS, c));
}

int		count_shell_spec(char *str)
{
	int	i;
	int	nb_spec;

	i = 0;
	nb_spec = 0;
	while (str[i])
	{
		if (is_shell_spec(str[i]))
			nb_spec++;
		i++;
	}
	return (nb_spec);
}
