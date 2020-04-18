/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:31:26 by efischer          #+#    #+#             */
/*   Updated: 2020/04/17 20:07:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		init_tab(char **token_tab)
{
	token_tab[OR_IF] = "OR_IF";
	token_tab[PIPE] = "PIPE";
	token_tab[AND_IF] = "AND_IF";
	token_tab[AND] = "AND";
	token_tab[GREATAND] = "GREATAND";
	token_tab[LESSAND] = "LESSAND";
	token_tab[ANDGREAT] = "ANDGREAT";
	token_tab[SEMI] = "SEMI";
	token_tab[DGREAT] = "DGREAT";
	token_tab[DLESS] = "DLESS";
	token_tab[DLESSDASH] = "DLESSDASH";
	token_tab[GREAT] = "GREAT";
	token_tab[LESS] = "LESS";
	token_tab[WORD] = "WORD";
	token_tab[IO_NB] = "IO_NB";
	token_tab[NEWLINE] = "NEWLINE";
}

static void	print(t_list *lst, t_list **elem)
{
	static char	*token_tab[NB_TOKEN];
	char		*print_content;
	char		*tmp;
	size_t		i;

	i = 0;
	print_content = NULL;
	init_tab(token_tab);
	while (i < NB_TOKEN)
	{
		tmp = NULL;
		if (((t_token*)(lst->content))->type == i)
		{
			if (i == WORD || i == IO_NB)
				tmp = ((t_token*)(lst->content))->value;
			ft_asprintf(&print_content, "%s -> [%s]\n", token_tab[i], tmp);
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
