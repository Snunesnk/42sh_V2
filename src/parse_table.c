/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enum_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:05:27 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 13:14:37 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_token_redir[] = { WORD, NONE };

int	g_token_start[] = { GREATAND, LESSAND, DGREAT, DLESS, GREAT, LESS, NEWLINE, IO_NB, WORD, NONE };

int	g_token_word[] = { SEMI, OR_IF, PIPE, AND_IF, GREATAND, LESSAND, ANDGREAT, AND, DGREAT, DLESS, GREAT, LESS, NEWLINE, IO_NB, WORD, NONE };

int	g_token_io_nb[] = { GREATAND, LESSAND, DGREAT, DLESS, GREAT, LESS, NONE };

int	g_token_if[] = { GREATAND, LESSAND, DGREAT, DLESS, LESS, GREAT, IO_NB, WORD, NONE };

int	g_token_pipe[] = { GREATAND, LESSAND, ANDGREAT, GREAT, LESS, WORD, NONE };

int	*g_parse_table[NB_TOKEN] =
{
	[OR_IF] = g_token_if,
	[AND_IF] = g_token_if,
	[PIPE] = g_token_pipe,
	[WORD] = g_token_word,
	[IO_NB] = g_token_io_nb,
	[SEMI] = g_token_start,
	[NEWLINE] = g_token_start,
	[AND] = g_token_start,
	[GREATAND] = g_token_redir,
	[LESSAND] = g_token_redir,
	[ANDGREAT] = g_token_redir,
	[DGREAT] = g_token_redir,
	[DLESS] = g_token_redir,
	[GREAT] = g_token_redir,
	[LESS] = g_token_redir
};
