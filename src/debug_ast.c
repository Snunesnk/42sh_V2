/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:31:34 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/13 17:09:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	debug_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == SEMI)
		ft_putendl("SEMI");
	else if (ast->type == AND)
		ft_putendl("AND");
	else if (ast->type == AND_IF)
		ft_putendl("AND_IF");
	else if (ast->type == OR_IF)
		ft_putendl("OR_IF");
	else if (ast->type == NONE)
		ft_putendl("NONE");
	debug(ast->content);
	if (ast->left != NULL)
	{
		ft_putstr("LEFT:");
		debug_ast(ast->left);
		debug(ast->content);
	}
	if (ast->right != NULL)
	{
		ft_putstr("RIGHT: ");
		debug_ast(ast->right);
	}
}
