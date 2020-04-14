/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_lexer_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:06:39 by efischer          #+#    #+#             */
/*   Updated: 2020/04/12 15:01:40 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*g_token_tab[NB_TOKEN] = {
	[SEMI] = ";",
	[OR_IF] = "||",
	[PIPE] = "|",
	[AND_IF] = "&&",
	[GREATAND] = ">&",
	[LESSAND] = "<&",
	[ANDGREAT] = "&>",
	[AND] = "&",
	[DGREAT] = ">>",
	[DLESSDASH] = "<<-",
	[DLESS] = "<<",
	[GREAT] = ">",
	[LESS] = "<",
	[NEWLINE] = "\n",
	[IO_NB] = NULL,
	[COMMENT] = NULL,
	[WORD] = NULL,
	[START] = NULL,
	[END] = NULL,
	[NONE] = NULL
};

int			launch_lexer_parser(char *input, t_ast **ast)
{
	t_list	*lst;

	lst = NULL;
	if (!lexer(input, &lst))
		if (!parser(lst))
			return (build_ast(ast, lst)); /* Here the bug comes from */
	return (FAILURE);
}
