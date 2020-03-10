/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enum_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:34:31 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 14:20:27 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		init_redir(enum e_token **enum_tab)
{
	static enum e_token	token_redir[] = { WORD, NONE };

	enum_tab[GREATAND] = token_redir;
	enum_tab[LESSAND] = token_redir;
	enum_tab[ANDGREAT] = token_redir;
	enum_tab[DGREAT] = token_redir;
	enum_tab[DLESS] = token_redir;
	enum_tab[GREAT] = token_redir;
	enum_tab[LESS] = token_redir;
}

static void		init_start(enum e_token **enum_tab)
{
	static enum e_token	token_start[] = { GREATAND, LESSAND, DGREAT, DLESS,
						GREAT, LESS, NEWLINE, IO_NB, COMMENT, WORD, END, NONE };

	enum_tab[SEMI] = token_start;
	enum_tab[NEWLINE] = token_start;
	enum_tab[AND] = token_start;
	enum_tab[START] = token_start;
}

static void		init_word(enum e_token **enum_tab)
{
	static enum e_token	token_word[] = { SEMI, OR_IF, PIPE, AND_IF, GREATAND,
						LESSAND, ANDGREAT, AND, DGREAT, DLESS, GREAT, LESS,
						NEWLINE, IO_NB, COMMENT, WORD, NONE };
	static enum e_token	token_io_nb[] = { GREATAND, LESSAND, DGREAT, DLESS,
						GREAT, LESS, NONE };

	enum_tab[WORD] = token_word;
	enum_tab[COMMENT] = token_word;
	enum_tab[IO_NB] = token_io_nb;
}

static void		init_if_pipe(enum e_token **enum_tab)
{
	static enum e_token	token_if[] = { GREATAND, LESSAND, DGREAT, DLESS, LESS,
						GREAT, IO_NB, COMMENT, WORD, NONE };
	static enum e_token	token_pipe[] = { GREATAND, LESSAND, ANDGREAT, GREAT,
						LESS, WORD, COMMENT, NONE };

	enum_tab[OR_IF] = token_if;
	enum_tab[AND_IF] = token_if;
	enum_tab[PIPE] = token_pipe;
}

enum e_token	**init_enum_tab(void)
{
	static enum e_token	*enum_tab[NB_TOKEN];

	init_redir(enum_tab);
	init_start(enum_tab);
	init_word(enum_tab);
	init_if_pipe(enum_tab);
	enum_tab[END] = NULL;
	return (enum_tab);
}
