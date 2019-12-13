/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:31:26 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:49:33 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static void	init_token_tab(char **token_tab)
{
	token_tab[PIPE] = "PIPE";
	token_tab[AND] = "AND";
	token_tab[SEMICOLON] = "SEMICOLON";
	token_tab[OP_BRACKET] = "OP_BRACKET";
	token_tab[CL_BRACKET] = "CL_BRACKET";
	token_tab[R_REDIR] = "R_REDIR";
	token_tab[L_REDIR] = "L_REDIR";
	token_tab[R_DB_REDIR] = "R_DB_REDIR";
	token_tab[L_DB_REDIR] = "L_DB_REDIR";
	token_tab[COMMENT] = "COMMENT";
	token_tab[WORD] = "WORD";
	token_tab[START] = "START";
	token_tab[END] = "END";
}

static void	print(t_list *lst, t_list **elem)
{
	static char	*token_tab[NB_TOKEN];
	char		*print_content;
	int		i;

	i = 0;
	print_content = NULL;
	init_token_tab(token_tab);
	while (i < NB_TOKEN)
	{
		if (((t_token*)(lst->content))->type == i)
		{
			ft_printf("%s -> [%s]\n", token_tab[i], ((t_token*)(lst->content))->value);
			break ;
		}
		i++;
	}
	*elem = ft_lstnew(print_content, ft_strlen(print_content));
	ft_strdel(&print_content);
}

void		debug(t_list *lst)
{
	ft_lstprint(lst, print);
}
