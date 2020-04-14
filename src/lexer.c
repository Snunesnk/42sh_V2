/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:59:39 by efischer          #+#    #+#             */
/*   Updated: 2020/04/14 12:36:59 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	add_token_to_list(t_token *token, t_list **lst)
{
	t_list	*new;

	new = ft_lstnew(token, sizeof(*token));
	if (!new)
		return (FAILURE);
	ft_lstaddend(lst, new);
	return (SUCCESS);
}

static int	border_token_list(t_list **lst, enum e_token token_type)
{
	t_token	token;

	ft_bzero(&token, sizeof(token));
	token.type = token_type;
	return (add_token_to_list(&token, lst));
}

int		get_token_list(char *input, t_list **lst)
{
	size_t			pos;
	t_token			token;
	int				ret;

	pos = 0;
	ret = SUCCESS;
	token.type = NONE;
	while (input[pos] && ret == SUCCESS)
	{
		while (ft_isblank(input[pos]))
			++pos;
		if (!input[pos])
			break ;
		token.value = NULL;
		pos += get_next_token(input + pos, &token);
		ret = add_token_to_list(&token, lst);
	}
	return (ret);
}

int			lexer(char *input, t_list **lst)
{
	int	ret;

	ret = FAILURE;
	if (!input)
		return (ret);
	while (ft_isblank(*input))
		++input;
	if ((input = ft_strjoin(input, "\n")) && *input)
		ret = border_token_list(lst, START) || get_token_list(input, lst)
			|| border_token_list(lst, END) || check_alias(lst, TRUE);
	ft_strdel(&input);
	return (ret);
}
