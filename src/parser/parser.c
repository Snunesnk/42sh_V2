/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:17:27 by efischer          #+#    #+#             */
/*   Updated: 2019/12/18 14:57:08 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	init_token_tab(int **token_tab)
{
	int		token_meta[NB_TOKEN] = { WHILE_WORD, WORD, COMMENT, TAB_END };
	int		token_word[NB_TOKEN] = { PIPE, AND, SEMI, OP_PARENTHESIS,
					CL_PARENTHESIS, WHILE_WORD, DONE, DGREAT, DLESS,
					GREAT, LESS, WORD, IO_NB, COMMENT, END, TAB_END };
	int		token_io_nb[NB_TOKEN] = { GREAT, LESS, DGREAT, DLESS, TAB_END };
	int		token_redir[NB_TOKEN] = { AND, WORD, COMMENT, TAB_END };
	int		token_semicolon[NB_TOKEN] = { WORD, COMMENT, CL_PARENTHESIS,
					WHILE_WORD, DONE, END, TAB_END };
	int		token_op_parenthesis[NB_TOKEN] = { OP_PARENTHESIS, CL_PARENTHESIS,
					WHILE_LOOP, WORD, COMMENT, TAB_END};
	int		token_while[NB_TOKEN] = { DONE, OP_PARENTHESIS, WORD, COMMENT,
					TAB_END};

	token_tab[OR_IF] = NULL;
	token_tab[PIPE] = token_meta;
	token_tab[AND_IF] = NULL;
	token_tab[AND] = token_meta;
	token_tab[DSEMI] = NULL;
	token_tab[SEMI] = token_semicolon;
	token_tab[OP_PARENTHESIS] = token_op_parenthesis;
	token_tab[CL_PARENTHESIS] = token_word;
	token_tab[WHILE_WORD] = token_while;
	token_tab[DONE] = token_word;
	token_tab[DGREAT] = token_redir;
	token_tab[DLESS] = token_redir;
	token_tab[GREAT] = token_redir;
	token_tab[LESS] = token_redir;
	token_tab[WORD] = token_word;
	token_tab[IO_NB] = token_io_nb;
	token_tab[COMMENT] = token_word;
	token_tab[START] = token_meta;
	token_tab[END] = NULL;
}

static void	init_bracket_tab(t_bracket *bracket_tab)
{
	t_bracket	parenthesis;
	t_bracket	while_loop;

	parenthesis.open = OP_PARENTHESIS;
	parenthesis.close = CL_PARENTHESIS;
	while_loop.open = WHILE_LOOP;
	while_loop.close = DONE;
	bracket_tab[PARENTHESIS] = parenthesis;
	bracket_tab[WHILE_LOOP] = while_loop;
}

static int	check_next_token(t_token *token, int *token_tab)
{
	size_t	token_index;
	int		ret;

	ret = FAILURE;
	token_index = 0;
	if (token_tab != NULL)
	{
		while (token_tab[token_index] != TAB_END)
		{
			if (token->type == (uint64_t)token_tab[token_index])
			{
				ret = SUCCESS;
				break ;
			}
			token_index++;
		}
	}
	return (ret);
}

static int	check_bracket(t_list *lst, uint64_t *buffer, size_t index,
			t_bracket bracket)
{
	if (((t_token*)(lst->content))->type == bracket.close)
	{
		if (buffer[index] == bracket.open)
		{
			buffer[index] = 0;
			if (index > 0)
				index--;
			return (parser(lst, buffer, index));
		}
		return (FAILURE);
	}
	if (buffer[index] != 0)
		index++;
	buffer[index] = bracket.open;
	return (parser(lst, buffer, index));
}

int			bracket(t_list *lst, uint64_t *buffer, size_t index)
{
	static t_bracket	bracket_tab[NB_BRACKET];

	init_bracket_tab(bracket_tab);
	if (((t_token*)(lst->content))->type == OP_PARENTHESIS
		|| ((t_token*)(lst->content))->type == CL_PARENTHESIS)
		return (check_bracket(lst, buffer, index, bracket_tab[PARENTHESIS]));
	return (check_bracket(lst, buffer, index, bracket_tab[WHILE_LOOP]));
}

int			parser(t_list *lst, uint64_t *buffer, size_t index)
{
	static int	*token_tab[NB_TOKEN];
	int			token_index;
	int			ret;
	
	init_token_tab(token_tab);
	if (lst->next == NULL)
	{
		if (buffer[0] == 0)
			return (SUCCESS);
		return (FAILURE);
	}
	token_index = ((t_token*)(lst->content))->type;
	lst = lst->next;
	ret = check_next_token(lst->content, token_tab[token_index]);
	if (ret == SUCCESS)
	{
		if (((t_token*)(lst->content))->type == OP_PARENTHESIS
			|| ((t_token*)(lst->content))->type == CL_PARENTHESIS
			|| ((t_token*)(lst->content))->type == WHILE_WORD
			|| ((t_token*)(lst->content))->type == DONE)
			return (bracket(lst, buffer, index));
		return (parser(lst, buffer, index));
	}
	return (ret);
}
