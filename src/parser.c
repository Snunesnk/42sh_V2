/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/22 12:49:37 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"
#include "ft_readline.h"

static t_list	*subprompt(void)
{
	t_list	*lst;
	char	*input;
	char	*tmp;

	tmp = ft_readline("> ");
	input = ft_strjoin(tmp, "\n");
	lst = lexer(input);
	free(input);
	free(tmp);
	return (lst);
}

static int		lookahead(t_list *lst, int curr, int next)
{
	int	i;

	i = 0;
	while (g_parse_table[curr][i] != NONE)
	{
		if (g_parse_table[curr][i] == next)
		{
			heredoc(lst, curr, next);
			return (e_success);
		}
		++i;
	}
	return (e_syntax_error);
}

static int		ppar(t_list **lst, int curr_type, int next_type)
{
	if ((curr_type == LESS || curr_type == DLESS || curr_type == GREAT
		|| curr_type == DGREAT || curr_type == GREATAND || curr_type == LESSAND
		|| curr_type == ANDGREAT || curr_type == DLESSDASH)
		&& next_type == NEWLINE)
	{
		psherror(e_syntax_error, "newline", e_parsing_type);
		return (g_errordesc[e_syntax_error].code);
	}
	else if (next_type == NEWLINE)
	{
		free_lst((*lst)->next);
		(*lst)->next = NULL;
		(*lst)->next = subprompt();
		return (e_success);
	}
	else
	{
		psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type);
		return (g_errordesc[e_syntax_error].code);
	}
}

int				parser(t_list *lst)
{
	int	curr_type;
	int	next_type;
	int	ret;

	curr_type = ((t_token*)(lst->content))->type;
	if (lookahead(lst, NEWLINE, curr_type))
	{
		psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type);
		return (e_syntax_error);
	}
	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		if (lookahead(lst, curr_type, next_type))
		{
			if (!(ret = ppar(&lst, curr_type, next_type)))
				continue ;
			else
				return (ret);
		}
		lst = lst->next;
	}
	return (e_success);
}
