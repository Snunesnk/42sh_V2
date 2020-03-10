/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:01:12 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 12:06:24 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	init_token_tab(char **token_tab)
{
	token_tab[OR_IF] = "||";
	token_tab[PIPE] = "|";
	token_tab[AND_IF] = "&&";
	token_tab[GREATAND] = ">&";
	token_tab[LESSAND] = "<&";
	token_tab[ANDGREAT] = "&>";
	token_tab[AND] = "&";
	token_tab[SEMI] = ";";
	token_tab[DGREAT] = ">>";
	token_tab[DLESS] = "<<";
	token_tab[DLESSDASH] = "<<-";
	token_tab[GREAT] = ">";
	token_tab[LESS] = "<";
	token_tab[NEWLINE] = "\n";
	token_tab[IO_NB] = NULL;
	token_tab[COMMENT] = NULL;
	token_tab[WORD] = NULL;
	token_tab[START] = NULL;
	token_tab[END] = NULL;
	token_tab[NONE] = NULL;
}

int			get_next_token(const char *str, t_token *token,
					enum e_token *last_token_type)
{
	char	*token_tab[NB_TOKEN];
	size_t	token_index;
	size_t	pos;

	pos = 0;
	token_index = 0;
	init_token_tab(token_tab);
	while (token_index < NB_TOKEN)
	{
		if (ft_strnequ(str, token_tab[token_index],
				ft_strlen(token_tab[token_index])) == TRUE)
		{
			token->type = token_index;
			pos = ft_strlen(token_tab[token_index]);
			break ;
		}
		token_index++;
	}
	if (token_index == NB_TOKEN)
		pos = get_word(str, token, last_token_type);
	return (pos);
}
