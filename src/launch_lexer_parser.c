/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_lexer_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:06:39 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 13:29:29 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*g_grammar[NB_TOKEN];

static void	init_token_tab(char **token_tab)
{
	token_tab[SEMI] = ";";
	token_tab[OR_IF] = "||";
	token_tab[PIPE] = "|";
	token_tab[AND_IF] = "&&";
	token_tab[GREATAND] = ">&";
	token_tab[LESSAND] = "<&";
	token_tab[ANDGREAT] = "&>";
	token_tab[AND] = "&";
	token_tab[DGREAT] = ">>";
	token_tab[DLESSDASH] = "<<-";
	token_tab[DLESS] = "<<";
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

int			launch_lexer_parser(char *input, t_ast **ast)
{
	t_list	*lst;
	int		ret;

	lst = NULL;
	init_token_tab(g_grammar);
	ret = lexer(input, &lst);
	if (ret == SUCCESS)
	{
		ret = parser(lst);
		if (ret == SUCCESS)
			ret = build_ast(ast, lst);
	}
	return (ret);
}
