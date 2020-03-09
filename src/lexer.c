/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:59:39 by efischer          #+#    #+#             */
/*   Updated: 2020/03/05 10:33:43 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

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

int		lexer(char *str, t_list **lst)
{
	int			ret;
	size_t		pos;
	t_token		token;
	uint64_t	type;

	pos = 0;
	ret = SUCCESS;
	if (str == NULL)
		return (FAILURE);
	while (ft_isblank(str[pos]) == TRUE)
		pos++;
	if (str[pos] != '\0')
	{
		ret = border_token_list(lst, START);
		while (str[pos] != '\0')
		{
			type = NONE;
			while (ft_isblank(str[pos]) == TRUE)
				pos++;
			if (str[pos] == '\0')
				break ;
			ft_bzero(&token, sizeof(token));
			pos += get_next_token(str + pos, &token, &type);
			add_token_to_list(&token, lst);
			type = token.type;
		}
		ret = border_token_list(lst, END);
	}
	return (ret);
}
