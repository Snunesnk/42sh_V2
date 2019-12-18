/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:45 by efischer          #+#    #+#             */
/*   Updated: 2019/12/18 13:01:28 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

#define TRUE 1
#define FALSE 0

static int		ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
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

static int	get_token_list(const char *str, t_list **lst)
{
	t_token	token;
	size_t	last_pos;
	size_t	pos;
	int		ret;

	pos = 0;
	ret = SUCCESS;
	while (str[pos] != '\0')
	{
		while (ft_isblank(str[pos]) == TRUE)
			pos++;
		if (str[pos] == '\0')
			break ;
		ft_bzero(&token, sizeof(token));
		last_pos = pos;
		pos += get_next_token(str + pos, &token);
		ret = add_token_to_list(&token, lst);
		if (pos == last_pos || ret == FAILURE)
		{
			ret = FAILURE;
			break ;
		}
	}
	return (ret);
}

int			lexer(const char *str, t_list **lst)
{
	int		ret;

	ret = border_token_list(lst, START);
	if (ret == SUCCESS)
	{
		ret = get_token_list(str, lst);
		if (ret == SUCCESS)
			ret = border_token_list(lst, END);
	}
	return (ret);
}
