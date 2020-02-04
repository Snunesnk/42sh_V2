/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:59:39 by efischer          #+#    #+#             */
/*   Updated: 2020/02/04 15:58:04 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int		ft_is_space_tab(int c)
{
	int		ret;

	ret = FALSE;
	if (c == ' ' || c == '\t')
		ret = TRUE;
	return (ret);
}

static void		astadd_left(t_ast **ast, t_ast *new_ast)
{
	t_ast	*head;

	head = *ast;
	if (*ast == NULL)
		*ast = new_ast;
	else
	{
		while ((*ast)->left != NULL)
			*ast = (*ast)->right;
		(*ast)->left = new_ast;
		*ast = head;
	}
}

static void		astadd_right(t_ast **ast, t_ast *new_ast)
{
	t_ast	*head;

	head = *ast;
	if (*ast == NULL)
		*ast = new_ast;
	else
	{
		while ((*ast)->right != NULL)
			*ast = (*ast)->right;
		(*ast)->right = new_ast;
		*ast = head;
	}
}

static t_ast	*astnew(t_list *lst, uint64_t type)
{
	t_ast	*ast;

	ast = (t_ast*)malloc(sizeof(t_ast));
	if (ast != NULL)
	{
		ft_bzero(ast, sizeof(t_ast));
		ast->type = type;
		ast->content = lst;
	}
	return (ast);
}

static int	add_token_to_list(t_token *token, t_list **lst)
{
	t_list	*new;
	int		ret;

	ret = SUCCESS;
	new = ft_lstnew(token, sizeof(*token));
	if (new == NULL)
		ret = FAILURE;
	ft_lstaddend(lst, new);
	return (ret);
}

static int	border_token_list(t_list **lst, uint64_t token_type)
{
	t_token	token;
	int		ret;

	ft_bzero(&token, sizeof(token));
	token.type = token_type;
	ret = add_token_to_list(&token, lst);
	return (ret);
}

static int	get_token_list(const char *str, size_t *pos, t_list **lst, uint64_t *type)
{
	t_token	token;
	t_token	last_token;
	size_t	last_pos;
	int		ret;

	ret = SUCCESS;
	while (str[*pos] != '\0')
	{
		while (ft_is_space_tab(str[*pos]) == TRUE)
			(*pos)++;
		if (str[*pos] == '\0')
			break ;
		ft_bzero(&token, sizeof(token));
		last_pos = *pos;
		*pos += get_next_token(str + *pos, &token);
		if (last_token.type == DLESS && token.type == WORD)
			token.type = END_OF_FILE;
		if (token.type == SEMI || token.type == OR_IF || token.type == AND_IF
			|| token.type == AND)
		{
			*type = token.type;
			break ;
		}
		ret = add_token_to_list(&token, lst);
		if (*pos == last_pos || ret == FAILURE)
		{
			ret = FAILURE;
			break ;
		}
		last_token = token;
	}
	return (ret);
}

int			lexer(const char *str, t_ast **ast)
{
	int			ret;
	uint64_t	type;
	size_t		pos;
	t_list		*lst;
	t_ast		*new_ast;

	pos = 0;
	while (str[pos] != '\0')
	{
		type = NONE;
		lst = NULL;
		ret = border_token_list(&lst, START);
		if (ret == SUCCESS)
		{
			ret = get_token_list(str, &pos, &lst, &type);
			if (ret == SUCCESS)
				ret = border_token_list(&lst, END);
			else
				ret = FAILURE;
		}
		if (type != NONE)
		{
			new_ast = astnew(NULL, type);
			astadd_right(ast, new_ast);
			new_ast = astnew(lst, NONE);
			astadd_left(ast, new_ast);
		}
		else
		{
			new_ast = astnew(lst, type);
			astadd_right(ast, new_ast);
		}
	}
	return (ret);
}
