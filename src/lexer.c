/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:59:39 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 12:00:00 by efischer         ###   ########.fr       */
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

static int	border_token_list(t_list **lst, enum e_token token_type)
{
	t_token	token;
	int		ret;

	ft_bzero(&token, sizeof(token));
	token.type = token_type;
	ret = add_token_to_list(&token, lst);
	return (ret);
}

static int	get_token_list(char *input, t_list **lst)
{
	size_t			pos;
	t_token			token;
	enum e_token	type;
	int				ret;

	pos = 0;
	ret = SUCCESS;
	while (input[pos] != '\0')
	{
		type = NONE;
		while (ft_isblank(input[pos]) == TRUE)
			pos++;
		if (input[pos] == '\0')
			break ;
		ft_bzero(&token, sizeof(token));
		pos += get_next_token(input + pos, &token, &type);
		ret = add_token_to_list(&token, lst);
		type = token.type;
	}
	return (ret);
}

int			lexer(char *input, t_list **lst)
{
	int				ret;

	ret = SUCCESS;
	if (input == NULL)
		return (FAILURE);
	while (ft_isblank(*input) == TRUE)
		input++;
	input = ft_strjoin(input, "\n");
	if (*input != '\0')
	{
		ret = border_token_list(lst, START);
		if (ret == SUCCESS)
		{
			ret = get_token_list(input, lst);
			if (ret == SUCCESS)
				ret = border_token_list(lst, END);
		}
	}
	ft_strdel(&input);
	return (ret);
}
