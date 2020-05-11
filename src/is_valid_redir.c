/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:20:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/11 18:45:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_valid_redir(t_list *lst)
{
	int		i;
	t_token	*token;
	int		*redirs;

	if (!lst || !lst->content || !lst->next || !lst->next->content)
		return (0);
	redirs = g_parse_table[IO_NB];
	token = lst->content;
	i = 0;
	while (redirs[i] != (int)token->type && redirs[i] != NONE)
		++i;
	if (redirs[i] == NONE)
		return (0);
	token = lst->next->content;
	return (token->type == WORD);
}
