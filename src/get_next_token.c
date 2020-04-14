/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:01:12 by efischer          #+#    #+#             */
/*   Updated: 2020/04/12 19:57:20 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			get_next_token(const char *str, t_token *token,
					enum e_token *last_token_type)
{
	size_t	token_index;
	size_t	pos;

	pos = 0;
	token_index = 0;
	while (token_index < NB_TOKEN)
	{
		if (ft_strnequ(str, g_grammar[token_index],
				ft_strlen(g_grammar[token_index])) == TRUE)
		{
			token->type = token_index;
			pos = ft_strlen(g_grammar[token_index]);
			break ;
		}
		token_index++;
	}
	if (token_index == NB_TOKEN)
		pos = get_word(str, token, last_token_type);
	return (pos);
}
