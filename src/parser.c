/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 14:44:25 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"
#include "quotes.h"

static int	parse_error(int err, char *tokval)
{
	if (err == e_syntax_error)
		psherror(e_syntax_error, tokval, e_parsing_type);
	else
		psherror(err, NULL, e_invalid_type);
	return (g_errordesc[err].code);
}

static int		lookahead(int fd, t_list **lst, int curr, int next)
{
	int	i;
	int	ret;

	i = 0;
	while (g_parse_table[curr][i] != NONE)
	{
		if (g_parse_table[curr][i] == next)
		{
			if ((curr == DLESS || curr == DLESSDASH) && next == WORD)
			{
				if ((ret = subprompt(fd, lst, BSQUOTE)))
					return (ret);
			}
			return (e_success);
		}
		++i;
	}
	return (e_syntax_error);
}

static int		check_syntax(int fd, t_list **lst, int curr_type, int next_type)
{
	int	ret;

	if ((curr_type == LESS || curr_type == DLESS || curr_type == GREAT
		|| curr_type == DGREAT || curr_type == GREATAND || curr_type == LESSAND
		|| curr_type == ANDGREAT || curr_type == DLESSDASH)
		&& next_type == NEWLINE)
		return (psherror(e_syntax_error, "newline", e_parsing_type));
	else if (next_type == NEWLINE)
	{
		free_lst((*lst)->next);
		(*lst)->next = NULL; // Not needed
		if ((ret = subprompt(fd, &(*lst)->next, FULL_QUOTE))) // Parser claim
			return (ret);
		return (e_success);
	}
	else
		return (psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type));
}

int				parser(t_list *lst, int fd)
{
	int	curr_type;
	int	next_type;
	int	ret;

	curr_type = ((t_token*)(lst->content))->type;
	if ((ret = lookahead(fd, &lst, NEWLINE, curr_type)))
		return (parse_error(ret, g_tokval[curr_type]));
	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		if ((ret = lookahead(fd, &lst, curr_type, next_type)) == e_syntax_error)
		{
			if (!(ret = check_syntax(fd, &lst, curr_type, next_type)))
				continue ;
		}
		if (ret)
			return (parse_error(ret, g_tokval[curr_type]));
		lst = lst->next;
	}
	return (e_success);
}
