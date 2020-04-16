/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 19:35:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 11:09:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_ast	*alloc_node(int type, t_list *pipeline, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_memalloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->content = pipeline;
	node->left = left;
	node->right = right;
	return (node);
}
