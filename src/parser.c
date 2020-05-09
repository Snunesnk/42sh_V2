/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 11:44:28 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"

static int		lookahead(t_list *lst, int curr, int next)
{
	int	i;
	int	ret;

	i = 0;
	while (g_parse_table[curr][i] != NONE)
	{
		if (g_parse_table[curr][i] == next)
		{
			if ((ret = heredoc(lst, curr, next)))
				return (ret);
			return (e_success);
		}
		++i;
	}
	return (e_syntax_error);
}

static int		parser_input_claim(int fd, t_list **lst, int curr_type, int next_type)
{
	if ((curr_type == LESS || curr_type == DLESS || curr_type == GREAT
		|| curr_type == DGREAT || curr_type == GREATAND || curr_type == LESSAND
		|| curr_type == ANDGREAT || curr_type == DLESSDASH)
		&& next_type == NEWLINE)
	{
		psherror(e_syntax_error, "newline", e_parsing_type);
		return (e_syntax_error);
	}
	else if (next_type == NEWLINE)
	{
		free_lst((*lst)->next);
		(*lst)->next = NULL;
		if (!((*lst)->next = subprompt(fd)))
			return (e_invalid_input);
		return (e_success);
	}
	else
	{
		psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type);
		return (e_syntax_error);
	}
}

int				parser(t_list *lst, int fd)
{
	int	curr_type;
	int	next_type;
	int	ret;

	curr_type = ((t_token*)(lst->content))->type;
	if (lookahead(lst, NEWLINE, curr_type))
	{
		psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type);
		return (g_errordesc[e_syntax_error].code);
	}
	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		if ((ret = lookahead(lst, curr_type, next_type)) == e_syntax_error)
		{
			if (!(ret = parser_input_claim(fd, &lst, curr_type, next_type)))
				continue ;
			return (g_errordesc[ret].code);
		}
		else if (ret == e_invalid_input)
		{
			ft_printf("%s line: %d : e_invalid_input\n", __FILE__, __LINE__);//DEBUGG
			return (130); // Should be removed once signals in place
		}
		lst = lst->next;
	}
	return (e_success);
}
