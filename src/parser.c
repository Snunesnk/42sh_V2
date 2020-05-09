/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 22:25:49 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"

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
				if ((ret = subprompt(fd, &lst, SBQUOTES))) // Heredoc
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
		if ((ret = subprompt(fd, &(*lst)->next, FULL_MODE))) // Parser claim
		{
			ft_printf("%s, line: %s: ret: %d %s\n", __FILE__, __LINE__, ret, g_errordesc[ret]); // DEBUGG
			return (ret);
		}
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
	if (lookahead(fd, lst, NEWLINE, curr_type))
	{
		psherror(e_syntax_error, g_tokval[curr_type], e_parsing_type);
		return (g_errordesc[e_syntax_error].code);
	}
	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		if ((ret = lookahead(fd, lst, curr_type, next_type)) == e_syntax_error)
		{
			if (!(ret = check_syntax(fd, &lst, curr_type, next_type)))
				continue ;
			return (g_errordesc[ret].code);
		}
		else if (ret == e_invalid_input) // Check the diff value from subprompt
//		{
//			ft_printf("%s line: %d : e_invalid_input\n", __FILE__, __LINE__);//DEBUGG
			return (130); // Should be removed once signals in place ?
//		}
		lst = lst->next;
	}
	return (e_success);
}
