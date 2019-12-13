/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:17:27 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:47:13 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static void	init_token_tab(int **token_tab)
{
	int		token_meta[NB_TOKEN] = { WORD, COMMENT, TAB_END };
	int		token_word[NB_TOKEN] = { PIPE, AND, SEMICOLON, R_DB_REDIR,
					L_DB_REDIR, R_REDIR, L_REDIR, WORD, COMMENT, END, TAB_END };
	int		token_redir[NB_TOKEN] = { AND, WORD, COMMENT, TAB_END };
	int		token_semicolon[NB_TOKEN] = { WORD, COMMENT, END, TAB_END };

	token_tab[PIPE] = token_meta;
	token_tab[AND] = token_meta;
	token_tab[SEMICOLON] = token_semicolon;
	token_tab[OP_BRACKET] = NULL;
	token_tab[CL_BRACKET] = NULL;
	token_tab[R_DB_REDIR] = token_redir;
	token_tab[L_DB_REDIR] = token_redir;
	token_tab[R_REDIR] = token_redir;
	token_tab[L_REDIR] = token_redir;
	token_tab[WORD] = token_word;
	token_tab[COMMENT] = token_word;
	token_tab[START] = token_meta;
	token_tab[END] = NULL;
}

static int	check_next_token(t_token *token, int *token_tab)
{
	size_t	token_index;

	token_index = 0;
	if (token_tab != NULL)
	{
		while (token_tab[token_index] != TAB_END)
		{
			if (token->type == token_tab[token_index])
				return (EXIT_SUCCESS);
			token_index++;
		}
	}
	return (EXIT_FAILURE);
}

int			parser(t_list *lst)
{
	static int	*token_tab[NB_TOKEN];
	int			token_index;
	int			ret;

	init_token_tab(token_tab);
	while (lst->next != NULL)
	{
		token_index = ((t_token*)(lst->content))->type;
		lst = lst->next;
		ret = check_next_token(lst->content, token_tab[token_index]);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
