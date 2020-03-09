/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:17:27 by efischer          #+#    #+#             */
/*   Updated: 2020/03/09 15:29:59 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"

static int	check_next_token(enum e_token type, enum e_token *token_tab)
{
	enum e_token token_index;
	int		ret;

	ret = FAILURE;
	token_index = 0;
	if (token_tab != NULL)
	{
		while (token_tab[token_index] != NONE)
		{
			if (type == token_tab[token_index])
			{
				ret = SUCCESS;
				break ;
			}
			token_index++;
		}
	}
	return (ret);
}

static enum e_token **init_token_tab(void)
{
	static enum e_token	*token_tab[NB_TOKEN];

	static enum e_token	token_pipe[] = { GREATAND, LESSAND, ANDGREAT, GREAT, LESS,
						WORD, COMMENT, NONE };
	static enum e_token	token_start[] = { WORD, GREATAND, LESSAND,
						LESS, GREAT, DGREAT, DLESS, NEWLINE, IO_NB, COMMENT, END, NONE };
	static enum e_token	token_if[] = { WORD, GREATAND, LESSAND,
						LESS, GREAT, DGREAT, DLESS, IO_NB, COMMENT, NONE };
	static enum e_token	token_redir[] = { WORD, NONE };
	static enum e_token	token_word[] = { AND_IF, OR_IF, PIPE, GREATAND, LESSAND,
						ANDGREAT, AND, SEMI, DGREAT, DLESS, GREAT, LESS, NEWLINE, WORD, IO_NB,
						COMMENT, NONE };
	static enum e_token	token_io_nb[] = { GREAT, LESS, DGREAT, DLESS, GREATAND, LESSAND,
						NONE };

	token_tab[SEMI] = token_start;
	token_tab[OR_IF] = token_if;
	token_tab[PIPE] = token_pipe;
	token_tab[AND_IF] = token_if;
	token_tab[GREATAND] = token_redir;
	token_tab[LESSAND] = token_redir;
	token_tab[ANDGREAT] = token_redir;
	token_tab[AND] = token_start;
	token_tab[DGREAT] = token_redir;
	token_tab[DLESS] = token_redir;
	token_tab[GREAT] = token_redir;
	token_tab[LESS] = token_redir;
	token_tab[NEWLINE] = token_start;
	token_tab[WORD] = token_word;
	token_tab[IO_NB] = token_io_nb;
	token_tab[COMMENT] = token_word;
	token_tab[START] = token_start;
	token_tab[END] = NULL;
	return (token_tab);
}

static void	merge_list(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	if (lst2 != NULL)
	{
		tmp = lst2->next;
		ft_lstdelone(&lst1->next, &del);
		ft_lstdelone(&lst2, &del);
		lst1->next = tmp;
		debug(lst1);
	}
}

static int	subprompt(t_list *lst, enum e_token *token_tab)
{
	t_list	*new_lst;
	char	*tmp;
	int		ret;

	ret = FAILURE;
	new_lst = NULL;
	if (((t_token*)(lst->content))->type == PIPE
		|| ((t_token*)(lst->content))->type == AND_IF
		|| ((t_token*)(lst->content))->type == OR_IF)
	{
		tmp = ft_readline("> ");
		ret = lexer(tmp, &new_lst);
		if (ret == SUCCESS)
		{
			merge_list(lst, new_lst);
			ret = check_next_token(((t_token*)(lst->next->content))->type, token_tab);
		}
		ft_strdel(&tmp);
	}
	return (ret);
}


void		parse_error(enum e_token token, char *data)
{
	char	*grammar[] = {";", "||", "|", "&&", ">&", "<&", "&>", "&", ">>",
						"<<-", "<<", ">", "<", "newline", "IO", "Comment (#)", "Word"};
	

	ft_dprintf(2, "\n21sh: syntax error near unexpected token `%s'%s%s\n", grammar[token]
				, token < 14 ? "" : " -> ", token < 14 ? "" : data);
}

int			parser(t_list *lst)
{
	static enum e_token	**token_tab = NULL;
	enum e_token		curr_type;
	enum e_token		prev_type;
	char				*value;
	int					ret;

	ret = SUCCESS;
	if (token_tab == NULL)
		token_tab = init_token_tab();
	while (lst->next != NULL)
	{
		prev_type = ((t_token*)(lst->content))->type;
		curr_type = ((t_token*)(lst->next->content))->type;
		ret = check_next_token(curr_type, token_tab[prev_type]);
		if (ret == FAILURE && curr_type == NEWLINE)
		{
			ret = subprompt(lst, token_tab[prev_type]);
			curr_type = ((t_token*)(lst->next->content))->type;
		}
		if (ret == FAILURE)
			break ;
		lst = lst->next;
	}
	if (ret == FAILURE)
	{
		value = ((t_token*)(lst->content))->value;
		parse_error(curr_type, value);
	}
	return (ret);
}
