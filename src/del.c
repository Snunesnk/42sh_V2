/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:00 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 10:09:06 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

void	free_lst(t_list *lst)
{
	if (lst)
	{
		free_lst(lst->next);
		free_token(lst->content);
		free(lst);
	}
}

void	free_ast(t_ast *ast)
{
	if (ast)
	{
		if (ast->left)
			free_ast(ast->left);
		if (ast->right)
			free_ast(ast->right);
		free_lst(ast->content);
		free(ast);
	}
}

void	del_env(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_shell_var*)(content))->name);
	ft_strdel(&((t_shell_var*)(content))->value);
	free(content);
}

void	del(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}
