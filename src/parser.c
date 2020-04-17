/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/17 18:56:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"
#include "ft_readline.h"

static t_list	*subprompt(void)
{
	t_list	*lst;
	char	*input;

	input = ft_readline("> ");
	lst = lexer(input);
	free(input);
	return (lst);
}

static int		lookahead(int curr, int next)
{
	int	i;

	i = 0;
	while (g_parse_table[curr][i] != NONE)
	{
		if (g_parse_table[curr][i] == next)
			return (e_success);
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
//		ft_lstdelone(&(*lst)->next, &del);
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

	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		if (lookahead(curr_type, next_type))
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
