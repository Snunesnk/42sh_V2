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
	size_t	token_i;
	size_t	pos;

	pos = 0;
	token_i = 0;
	while (g_token_tab[token_i] && ft_strncmp(str,
		g_token_tab[token_i], ft_strlen(g_token_tab[token_i])))
		++token_i;
	if (!g_token_tab[token_i])
		pos = get_word(str, token, last_token_type);
	else
	{
		token->type = token_i;
		pos = ft_strlen(g_token_tab[token_i]);
	}
	return (pos);
}
