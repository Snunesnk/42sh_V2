/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:17:27 by efischer          #+#    #+#             */
/*   Updated: 2020/03/05 11:28:09 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	init_token_tab(int **token_tab)
{
	int		token_pipe[NB_TOKEN] = { GREATAND, LESSAND, ANDGREAT, LESS, GREAT,
					WHILE_WORD, WORD, COMMENT, TAB_END };
	int		token_start[NB_TOKEN] = { WHILE_WORD, WORD, GREATAND, LESSAND,
					LESS, GREAT, DGREAT, DLESS, IO_NB, COMMENT, END, TAB_END };
	int		token_if[NB_TOKEN] = { WHILE_WORD, WORD, GREATAND, LESSAND,
					LESS, GREAT, DGREAT, DLESS, IO_NB, COMMENT, TAB_END };
	int		token_redir[NB_TOKEN] = { WORD, TAB_END };
	int		token_word[NB_TOKEN] = { AND_IF, OR_IF, PIPE, GREATAND, LESSAND,
					ANDGREAT, AND, SEMI, OP_PARENTHESIS, CL_PARENTHESIS,
					WHILE_WORD, DONE, DGREAT, DLESS, GREAT, LESS, WORD, IO_NB,
					COMMENT, END, TAB_END };
	int		token_io_nb[NB_TOKEN] = { GREAT, LESS, DGREAT, DLESS, GREATAND, LESSAND,
					TAB_END };
	int		token_semi[NB_TOKEN] = { WORD, COMMENT, CL_PARENTHESIS,
					WHILE_WORD, DONE, END, TAB_END };
	int		token_op_parenthesis[NB_TOKEN] = { OP_PARENTHESIS, CL_PARENTHESIS,
					WHILE_LOOP, WORD, COMMENT, TAB_END};
	int		token_while[NB_TOKEN] = { DONE, OP_PARENTHESIS, WORD, COMMENT,
					TAB_END};

	token_tab[OR_IF] = token_if;
	token_tab[PIPE] = token_pipe;
	token_tab[AND_IF] = token_if;
	token_tab[GREATAND] = token_redir;
	token_tab[LESSAND] = token_redir;
	token_tab[ANDGREAT] = token_redir;
	token_tab[AND] = token_start;
	token_tab[DSEMI] = NULL;
	token_tab[SEMI] = token_semi;
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
	token_tab[START] = token_start;
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

static int	check_next_token(uint64_t type, int *token_tab)
{
	size_t	token_index;
	int		ret;

	ret = FAILURE;
	token_index = 0;
	if (token_tab != NULL)
	{
		while (token_tab[token_index] != TAB_END)
		{
			if (type == (uint64_t)token_tab[token_index])
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
			return (do_parsing(lst, buffer, index));
		}
		return (FAILURE);
	}
	if (buffer[index] != 0)
		index++;
	buffer[index] = bracket.open;
	return (do_parsing(lst, buffer, index));
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

static void	merge_list(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	tmp = lst2->next;
	ft_lstdelone(&lst1->next, &del);
	ft_lstdelone(&lst2, &del);
	lst1->next = tmp;
}

static int	subprompt(t_list *lst, int *token_tab)
{
	t_list	*new_lst;
	char	*tmp;
	int		ret;

	ret = FAILURE;
	if (((t_token*)(lst->content))->type == PIPE
		|| ((t_token*)(lst->content))->type == AND_IF
		|| ((t_token*)(lst->content))->type == OR_IF)
	{
		tmp = readline("> ");
		ret = lexer(tmp, &new_lst);
		if (ret == SUCCESS)
		{
			merge_list(lst, new_lst);
			ret = check_next_token(((t_token*)(lst->next->content))->type, token_tab);
		}
	}
	return (ret);
}

int			do_parsing(t_list *lst, uint64_t *buffer, size_t index)
{
	static int	*token_tab[NB_TOKEN];
	uint64_t	token_type;
	int			token_index;
	int			ret;

	ret = SUCCESS;
	init_token_tab(token_tab);
	if (lst->next != NULL)
	{
		token_index = ((t_token*)(lst->content))->type;
		token_type = ((t_token*)(lst->next->content))->type;
		ret = check_next_token(token_type, token_tab[token_index]);
		if (ret == FAILURE && token_type == END)
			ret = subprompt(lst, token_tab[token_index]);
		lst = lst->next;
		if (ret == SUCCESS)
		{
			if (token_type == OP_PARENTHESIS || token_type == CL_PARENTHESIS
				|| token_type == WHILE_WORD || token_type == DONE)
				ret = bracket(lst, buffer, index);
			else
				ret = do_parsing(lst, buffer, index);
		}
	}
	return (ret);
}

int			parser(t_list *lst)
{
	int			ret;
	size_t		index;
	uint64_t	buffer[BUF_SIZE];

	ret = SUCCESS;
	index = 0;
	ft_bzero(buffer, sizeof(buffer));
	ret = do_parsing(lst, buffer, index);
	if (buffer[0] != 0)
		ret = FAILURE;
	return (ret);
}
